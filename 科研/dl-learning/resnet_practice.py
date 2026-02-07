import torch
from torch import nn
import pandas as pd
import torch.optim as optim
import torch.nn.functional as F
import torchvision.transforms as T
from torch.utils.data import DataLoader,Dataset
import os
from PIL import Image
from tqdm import tqdm
from torch.utils.data import random_split
import torchvision.models as models

base_path = ""
out_path = ""
save_path = ""
batch_size = 128
transform = T.Compose[
    T.ToTensor
]
train_df = pd.read_csv(os.path.join(base_path,"train.csv"))
val_df = pd.read_csv(os.path.join(base_path,"test.csv"))
label_counts = train_df['label'].value_counts

unique_labels = train_df["label"].unique
label2index = {label: idx for idx,label in enumerate(unique_labels)}
index2label = {v: k for k,v in label2index.items()}

class LeaveDataset(Dataset):
    def __init__(self,data_df,transform = None):
        super().__init__()
        self.data = data_df
        self.transform = transform
    
    def __len__(self):
        return len(self.data)
    
    def __getitem__(self, index):
        image_path = os.path.join(base_path,self.data.iloc[index,0])
        image  = Image.open(image_path)
        if(self.transform):
            image = self.transform(image)
        label_name = self.data.iloc(index,1)
        label = label2index[label_name]
        return image,label
    
train_dataset = LeaveDataset(train_df,transform)

total_size = len(train_dataset)
test_size = int(0.2*total_size)
train_size = total_size-test_size

train_subset,test_subset = random_split(train_dataset,[train_size,test_size])
train_loader = DataLoader(train_subset,batch_size = batch_size,shuffle = True,num_workers=4)
test_loader = DataLoader(test_subset,batch_size = batch_size,shuffle=False,num_workers=4)

resnet = models.resnet18(weights=models.ResNet18_Weights.DEFAULT)

num_classes = len(label_counts)

resnet.fc = torch.nn.Linear(resnet.fc.in_features,num_classes)
device = torch.device("cuda" if torch.cuda.is_available else "cpu")

resnet = resnet.to(device)

criterion = nn.CrossEntropyLoss()
lr,momentum = 0.01,0.9
optimizer = optim.sgd(resnet.parameters,lr = lr,momentum = momentum)

def train():
    resnet.train()
    batch_nums = len(train_loader)
    batch_size = train_loader.batch_size
    size = len(train_loader.dataset)

    train_loss,correct = 0.0,0.0
    p = tqdm(train_loader,desc = "Training",unit = "batch")

    for X,y in p:
        X,y = X.to(device),y.to(device)
        pred = resnet(X)
        loss = criterion(pred,y)
        loss.backward()
        optimizer.step()
        optimizer.zero_grad()

        p.set_postfix(loss = f"{loss.item:>8f}")
        train_loss+=loss.item()
        correct+=(pred.argmax(1)==y).sum.item
    train_loss /= batch_nums
    correct /= size
    print(f"Train Accuracy: {(100*correct):>0.2f}%, Train Avg loss: {train_loss:>8f}")
    return train_loss,correct
def test():
    resnet.eval()
    batch_nums = len(test_loader)
    batch_size = test_loader.batch_size
    size = len(test_loader.dataset)

    test_loss,correct = 0.0,0.0

    with torch.no_grad():
        for X,y in test_loader:
            X,y = X.to(device),y.to(device)
            pred = resnet(X)
            loss = criterion(pred,y)
            test_loss+=loss.item()
            correct+=(pred.argmax(1) == y).sum().item()
        test_loss /= batch_nums
        correct /= size
        print(f"Test Accuracy: {(100*correct):>0.1f}%, Test Avg loss: {test_loss:>8f}")
        return test_loss,correct
    

train_losses,train_accs = [],[]
test_losses,test_accs = [],[]
epochs = 20
best_acc = 0.0

for epoch in range(epochs):
    print(f"Epoch{epoch+1}")
    train_loss,train_acc = train()
    train_losses.append(train_loss)
    train_accs.append(train_acc)

    test_loss,test_acc = test()
    test_losses.append(test_loss)
    test_accs.append(test_acc)

    if test_acc >best_acc:
        best_acc = test_acc
        torch.save(resnet.state_dict(),save_path)
        print(f'New best model saved with accuracy: {best_acc:.4f}')
    print("-"*30)
    


    