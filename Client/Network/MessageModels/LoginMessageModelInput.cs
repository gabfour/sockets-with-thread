using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Client.Network.MessageModels
{
    public class LoginMessageModelInput : MessageModelDefault
    {
        public string username { get; set; }
    }
}
