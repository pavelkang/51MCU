import Tkinter,serial
a=serial.Serial()
a.port=5
a.baudrate=9600
a.open()

class MainWindow(Tkinter.Frame):
    def __init__(self):
        Tkinter.Frame.__init__(self)
        self.rowconfigure(0,weight=1)
        self.columnconfigure(0,weight=1)
        self.createWidgets()
        self.binaryCommand = '0b11111111'
        
    def createWidgets(self):
        #create a frame with 8 buttons,style
        
        buttonFrame = Tkinter.LabelFrame(self,bd=2,height=400,width=600,labelanchor='nw',text='choose LEDs')
        buttonFrame.columnconfigure(1,weight=1)
        buttonFrame.pack(fill=Tkinter.BOTH,expand=1)    
        #buttons
        self.button1 = Tkinter.Checkbutton(buttonFrame,text='1',command=self.changeOutPut1,activebackground='#ff0').pack(fill=Tkinter.X)
        self.button2 = Tkinter.Checkbutton(buttonFrame,text='2',command=self.changeOutPut2,activebackground='#f00').pack(fill=Tkinter.X)
        self.button3 = Tkinter.Checkbutton(buttonFrame,text='3',command=self.changeOutPut3,activebackground='#0f0').pack(fill=Tkinter.X)
        self.button4 = Tkinter.Checkbutton(buttonFrame,text='4',command=self.changeOutPut4,activebackground='#f00').pack(fill=Tkinter.X)
        self.button5 = Tkinter.Checkbutton(buttonFrame,text='5',command=self.changeOutPut5,activebackground='#ff0').pack(fill=Tkinter.X)
        self.button6 = Tkinter.Checkbutton(buttonFrame,text='6',command=self.changeOutPut6,activebackground='#f00').pack(fill=Tkinter.X)
        self.button7 = Tkinter.Checkbutton(buttonFrame,text='7',command=self.changeOutPut7,activebackground='#0f0').pack(fill=Tkinter.X)
        self.button8 = Tkinter.Checkbutton(buttonFrame,text='8',command=self.changeOutPut8,activebackground='#f00').pack(fill=Tkinter.X)
        #GO
        GoFrame = Tkinter.Frame(self)
        Tkinter.Button(GoFrame,text="Send!",command=self.sendSignal).pack()
        GoFrame.pack(anchor=Tkinter.W,fill=Tkinter.X)
        self.pack()
    def changeOutPut1(self):
        flag = self.binaryCommand[2]
        if flag=='0':
            print self.binaryCommand
            self.binaryCommand = self.binaryCommand[0:2]+'1'+self.binaryCommand[3:]
            
        if flag=='1':
            print self.binaryCommand
            self.binaryCommand = self.binaryCommand[0:2]+'0'+self.binaryCommand[3:]
    def changeOutPut2(self):
        flag = self.binaryCommand[3]
        if flag=='0':
            print self.binaryCommand
            self.binaryCommand = self.binaryCommand[0:3]+'1'+self.binaryCommand[4:]
            
        if flag=='1':
            print self.binaryCommand
            self.binaryCommand = self.binaryCommand[0:3]+'0'+self.binaryCommand[4:]
    def changeOutPut3(self):
        flag = self.binaryCommand[4]
        if flag=='0':
            print self.binaryCommand
            self.binaryCommand = self.binaryCommand[0:4]+'1'+self.binaryCommand[5:]
            
        if flag=='1':
            print self.binaryCommand
            self.binaryCommand = self.binaryCommand[0:4]+'0'+self.binaryCommand[5:]
    def changeOutPut4(self):
        flag = self.binaryCommand[5]
        if flag=='0':
            print self.binaryCommand
            self.binaryCommand = self.binaryCommand[0:5]+'1'+self.binaryCommand[6:]
            
        if flag=='1':
            print self.binaryCommand
            self.binaryCommand = self.binaryCommand[0:5]+'0'+self.binaryCommand[6:]
    def changeOutPut5(self):
        flag = self.binaryCommand[6]
        if flag=='0':
            print self.binaryCommand
            self.binaryCommand = self.binaryCommand[0:6]+'1'+self.binaryCommand[7:]
            
        if flag=='1':
            print self.binaryCommand
            self.binaryCommand = self.binaryCommand[0:6]+'0'+self.binaryCommand[7:]
    def changeOutPut6(self):
        flag = self.binaryCommand[7]
        if flag=='0':
            print self.binaryCommand
            self.binaryCommand = self.binaryCommand[0:7]+'1'+self.binaryCommand[8:]
            
        if flag=='1':
            print self.binaryCommand
            self.binaryCommand = self.binaryCommand[0:7]+'0'+self.binaryCommand[8:]
    def changeOutPut7(self):
        flag = self.binaryCommand[8]
        if flag=='0':
            print self.binaryCommand
            self.binaryCommand = self.binaryCommand[0:8]+'1'+self.binaryCommand[9:]
            
        if flag=='1':
            print self.binaryCommand
            self.binaryCommand = self.binaryCommand[0:8]+'0'+self.binaryCommand[9:]
    def changeOutPut8(self):
        flag = self.binaryCommand[9]
        if flag=='0':
            print self.binaryCommand
            self.binaryCommand = self.binaryCommand[0:9]+'1'+self.binaryCommand[10:]
            
        if flag=='1':
            print self.binaryCommand
            self.binaryCommand = self.binaryCommand[0:9]+'0'+self.binaryCommand[10:] 
    def getHexB(self,x):
        if x%2 == 0:
            hexer=x.decode("hex")
        else:
            x = x[:-1]+'0'+x[-1]
            hexer=x.decode("hex")
        return hexer
    def getHexA(self):
        return hex(eval(self.binaryCommand))[2:]
    
    def sendSignal(self):
        a.write(self.getHexB(self.getHexA()))
        print 'signal is ', self.getHexB(self.getHexA())

        

if __name__ == "__main__":
    App=MainWindow()
    App.mainloop()
        
        
