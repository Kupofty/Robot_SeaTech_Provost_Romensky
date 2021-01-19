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

            serialPort1 = new ReliableSerialPort("COM4", 115200, Parity.None, 8, StopBits.One);
            serialPort1.DataReceived += SerialPort1_DataReceived; 
            serialPort1.Open();

            timerAffichage = new DispatcherTimer();
            timerAffichage.Interval = new TimeSpan(0, 0, 0, 0, 100);
            timerAffichage.Tick += TimerAffichage_Tick; ;
            timerAffichage.Start();


        }


        private void TimerAffichage_Tick(object sender, EventArgs e)
        {
            while(robot.byteListReceived.Count>0)
            {
                TextBoxReception.Text += "0x" + robot.byteListReceived.Dequeue().ToString("X2") + " ";
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
            byte[] byteList = new byte[20];
            for (int i = 0; i < 20; i++)
            {
                byteList[i] = (byte)(2 * i);             
            }       
            serialPort1.Write(byteList, 0, byteList.Length);   
        }


        private void TextBoxEmission_KeyUp(object sender, KeyEventArgs e)
        {
            if (e.Key == Key.Enter)
                SendMessage();
        }


        private void SendMessage()
        {
            serialPort1.WriteLine(TextBoxEmission.Text);
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
                    ...
                        break;
                case StateReception.FunctionMSB:
                    ...
                        break;
                case StateReception.FunctionLSB:
                    ...
                        break;
                case StateReception.PayLoadLengthMSB:
                    ...
                        break;
                case StateReception.PayLoadLengthLSB:
                    ...
                        break;
                case StateReception.Payload:
                    ...
                        break;
                case StateReception.Checksum:
                    ...
                    if(calculatedChecksum== receivedChecksum)
                    {
                        //success on a un message valide
                    }
                    ...
                    break;
                default:
                    rcvState = StateReception.Waiting;
                    break;
            }
        }


    }
}


