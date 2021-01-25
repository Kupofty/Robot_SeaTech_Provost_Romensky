using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.IO.Ports;
using ExtendedSerialPort;
using System.Windows.Threading;


namespace Projet_Robot_interface_turbo_PRVST_RMSK
{
    /// <summary>
    /// Logique d'interaction pour MainWindow.xaml
    /// </summary>
    
    public partial class MainWindow : Window
    {
        ReliableSerialPort serialPort1;
        Robot robot = new Robot();
        DispatcherTimer timerAffichage;

        public MainWindow()
        {
            InitializeComponent();

            serialPort1 = new ReliableSerialPort("COM5", 115200, Parity.None, 8, StopBits.One);
            serialPort1.DataReceived += SerialPort1_DataReceived; 
            serialPort1.Open();
            

            timerAffichage = new DispatcherTimer();
            timerAffichage.Interval = new TimeSpan(0, 0, 0, 0, 100);
            timerAffichage.Tick += TimerAffichage_Tick; ;
            timerAffichage.Start();


        }
        bool iscorrectChecksum;

        private void TimerAffichage_Tick(object sender, EventArgs e)
        {
            while(robot.byteListReceived.Count>0)
            {
                byte c = robot.byteListReceived.Dequeue();
                TextBoxReception.Text += "0x" + c.ToString("X2") + " ";
                DecodeMessage(c);
            }
        }


        public void SerialPort1_DataReceived(object sender, DataReceivedArgs e)
        {
            for (int i = 0; i < e.Data.Length; i++)
            {
                robot.byteListReceived.Enqueue(e.Data[i]);

            }
            //foreach(var c in e.Data)
            //{
            //    robot.byteListReceived.Enqueue(c);
            //}
        }


        private void TextBox_TextChanged(object sender, TextChangedEventArgs e)
        {
            
        }

        private void TextBox_TextChanged_1(object sender, TextChangedEventArgs e)
        {
            
        }


        bool cpt=true;
        private void buttonEnvoyer_Click(object sender, RoutedEventArgs e)
        {
            if( cpt)
                buttonEnvoyer.Background = Brushes.RoyalBlue;
            else
                buttonEnvoyer.Background = Brushes.Beige;
            cpt=!cpt ;
            SendMessage();
        }

        private void buttonClear_Click(object sender, RoutedEventArgs e)
        {
            TextBoxReception.Text = "";
        }



        private void buttonTest_Click(object sender, RoutedEventArgs e)
        {
            byte[] byteList = new byte[4];
            byteList[0] = 0x00;
            byteList[1] = 0x020;
            byteList[2] = 0x01;
            byteList[3] = 0x00;
            //for (int i = 0; i < 20; i++)
            //{
            //    byteList[i] = (byte)(2 * i);             
            //}       
            serialPort1.Write(byteList, 0, byteList.Length);   

        }


        private void TextBoxEmission_KeyUp(object sender, KeyEventArgs e)
        {
            if (e.Key == Key.Enter)
                SendMessage();
        }


        private void SendMessage()
        {
            //serialPort1.WriteLine(TextBoxEmission.Text);
            byte[] bytes = Encoding.ASCII.GetBytes(TextBoxEmission.Text);
            UartEncodeAndSendMessage(0x0080, bytes.Length, bytes);
            TextBoxEmission.Text = "";
        }

        byte CalculateChecksum(int msgFunction, int msgPayloadLength, byte []  msgPayload)
        {
            byte Checksum;
            Checksum = 0xFE;
            Checksum ^= (byte) (msgFunction >> 8);
            Checksum ^= (byte)(msgFunction);
            Checksum ^= (byte)(msgPayloadLength >> 8);
            Checksum ^= (byte)(msgPayloadLength);
            for (int i = 0; i < msgPayloadLength; i++)
                Checksum ^= msgPayload[i];
            return Checksum ;
        }

        void UartEncodeAndSendMessage(int msgFunction, int msgPayloadLength, byte [] msgPayload)
        {
            byte [] message = new byte [msgPayloadLength+6];
            int pos = 0;
            message[pos++] = 0xFE;
            message[pos++] = (byte)(msgFunction >> 8);
            message[pos++] = (byte)(msgFunction >> 0);
            message[pos++] = (byte)(msgPayloadLength >> 8);
            message[pos++] = (byte)(msgPayloadLength >> 0);
            for (int i = 0; i < msgPayloadLength; i++)
                message[pos++]= msgPayload[i];
            message[pos++] = CalculateChecksum(msgFunction, msgPayloadLength, msgPayload);
            serialPort1.Write(message,0,message.Length);
        }
        
        public enum StateReception
        {
            Waiting,
            FunctionMSB,
            FunctionLSB,
            PayLoadLengthMSB,
            PayLoadLengthLSB,
            Payload,
            Checksum
        }

        StateReception rcvState = StateReception.Waiting;
        int msgDecodedFunction = 0;
        int msgDecodedPayloadLength = 0;
        byte[] msgDecodedPayload;
        int msgDecodedPayloadIndex = 0;
        
        private void DecodeMessage(byte c)
        {
            switch(rcvState)
            {
                case StateReception.Waiting:
                    if (c == 0xFE)
                    {
                        rcvState = StateReception.FunctionMSB;
                    }
                        break;
                case StateReception.FunctionMSB:
                    msgDecodedFunction = (int)(c << 8);
                    rcvState = StateReception.FunctionLSB;
                    break;
                case StateReception.FunctionLSB:
                    msgDecodedFunction += (int)(c<<0 );
                    rcvState = StateReception.PayLoadLengthMSB;
                    break;
                case StateReception.PayLoadLengthMSB:
                    msgDecodedPayloadLength= (int)(c << 8);
                    rcvState = StateReception.PayLoadLengthLSB;
                    break;
                case StateReception.PayLoadLengthLSB:
                    msgDecodedPayloadLength += (int)(c<<0);
                    if(msgDecodedPayloadLength==0)
                        rcvState = StateReception.Checksum;
                    else if(msgDecodedPayloadLength > 512)
                        rcvState = StateReception.Waiting;
                    else
                    {
                        rcvState = StateReception.Payload;
                        msgDecodedPayloadIndex = 0;
                        msgDecodedPayload = new byte[msgDecodedPayloadLength];
                    }
                    break;
                case StateReception.Payload:
                    msgDecodedPayload[msgDecodedPayloadIndex++] = c;
                    if  (msgDecodedPayloadIndex==msgDecodedPayloadLength)
                    { 
                        rcvState = StateReception.Checksum;
                    }
                    break;

                case StateReception.Checksum:
                    
                    byte receivedChecksum = c;
                    byte calculatedChecksum = CalculateChecksum(msgDecodedFunction, msgDecodedPayloadLength, msgDecodedPayload);
                    if(calculatedChecksum == receivedChecksum)
                    {
                        iscorrectChecksum = true;
                        ProcessDecodedMessage(msgDecodedFunction, msgDecodedPayloadLength, msgDecodedPayload);
                    }
                    else
                        iscorrectChecksum = false;
                    break;
                default:
                    rcvState = StateReception.Waiting;
                    break;
            }
        }
        void ProcessDecodedMessage(int msgFunction, int msgPayloadLength, byte[] msgPayload)
        {
                if (msgFunction == (int)0x0080 ) 
                     {}
                else if (msgFunction == (int)0x0020)   //led
                    if (msgDecodedPayload[0] ==0x00)      //num led
                        if (msgDecodedPayload[1] ==0x01)//etat led  
                        { } //led1 allumée
                        else
                        { } // led1 eteinte
                    else if (msgDecodedPayload[0] == 0x01) //num led
                        if (msgDecodedPayload[1] == 0x01)//etat led  
                        { } // led2 allumée
                        else
                        { } // led2 éteinte
                    else //num led
                         if (msgDecodedPayload[1] ==0x01)//etat led  
                       { } //led3 allumée
                         else
                       { } // led3 éteinte
                else if (msgFunction == (int)0x0030) // distance telemètre
                { int dist1 = (int)msgDecodedPayload[0]; // telemètre 1
                  int dist2 = (int)msgDecodedPayload[1]; //telemètre 2
                  int dist3 = (int)msgDecodedPayload[2]; }// telemètre 3

                else if (msgFunction ==(int)0x0040) //consigne vitesse
                { int vitesse1 = (int)msgDecodedPayload[0];
                  int vitesse2 = (int)msgDecodedPayload[1]; }
        }
        private void CheckBox_Checked_1(object sender, RoutedEventArgs e)
        {
           
        }

        private void CheckBox_Checked_2(object sender, RoutedEventArgs e)
        {
            //byte[] byteList = new byte[4];
            //byteList[0] = 0x00;
            //byteList[1] = 0x020;
            //byteList[2] = 0x02;
            //byteList[3] = 0x01;
            ////for (int i = 0; i < 20; i++)
            ////{
            ////    byteList[i] = (byte)(2 * i);             
            ////}       
            //serialPort1.Write(byteList, 0, byteList.Length);
        }

        private void CheckBox_Checked(object sender, RoutedEventArgs e)
        {
            //byte[] byteList = new byte[4];
            //byteList[0] = 0x00;
            //byteList[1] = 0x020;
            //byteList[2] = 0x03;
            //byteList[3] = 0x01;
            ////for (int i = 0; i < 20; i++)
            ////{
            ////    byteList[i] = (byte)(2 * i);             
            ////}       
            //serialPort1.Write(byteList, 0, byteList.Length);
        }

    
    }
}


