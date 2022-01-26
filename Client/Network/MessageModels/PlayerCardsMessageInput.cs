using Client.Models;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Client.Network.MessageModels
{
    public class PlayerCardsMessageInput : MessageModelDefault
    {
        public List<Card> Cards { get; set; }
    }
}
