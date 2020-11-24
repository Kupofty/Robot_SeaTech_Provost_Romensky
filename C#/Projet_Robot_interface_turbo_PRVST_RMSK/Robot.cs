using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Projet_Robot_interface_turbo_PRVST_RMSK
{
    class Robot
    {
        public string receivedText = "";
        public Queue<byte> byteListReceived = new Queue<byte>();
    }
}
