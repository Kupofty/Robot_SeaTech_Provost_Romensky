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


namespace Projet_Robot_interface_turbo_PRVST_RMSK
{
    /// <summary>
    /// Logique d'interaction pour MainWindow.xaml
    /// </summary>
    
    public partial class MainWindow : Window
    {
        ReliableSerialPort serialPort1;

        public MainWindow()
        {
            InitializeComponent();
            serialPort1 = new ReliableSerialPort("COM3", 115200, Parity.None, 8, StopBits.One);
            serialPort1.Open();
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

            SendMessage(1);


        }


        private void TextBoxEmission_KeyUp(object sender, KeyEventArgs e)
        {
            if (e.Key == Key.Enter)
                SendMessage(2);
        }


        private void SendMessage(int a)
        {
            TextBoxReception.Text += "Reçu : " + TextBoxEmission.Text;
            TextBoxEmission.Text = "";
            if (a == 1)
                TextBoxReception.Text += "\n";
        }
    }
}


