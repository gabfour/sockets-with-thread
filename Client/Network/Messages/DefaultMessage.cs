using Client.Network.MessageModels;
using Client.Utils;
using Newtonsoft.Json;
using Newtonsoft.Json.Linq;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Client.Network.Messages
{
    public abstract class DefaultMessage
    {
        private static string TAG = nameof(DefaultMessage);
        public static DefaultMessage? HandleMessage(Client client, string json)
        {
            JObject jsonObject;
            try
            {
                jsonObject = JObject.Parse(json);
            }
            catch (Exception e)
            {
                Output.LogError(TAG, $"Error while parsing json: " + e.Message);
                return null;
            }
            if (jsonObject == null || !jsonObject.ContainsKey("id") || !int.TryParse(jsonObject["id"]!.ToString(), out var id))
            {
                Output.LogError(TAG, $"Message id not found: " + json);
                return null;
            }

            DefaultMessage? result = null;
            switch (id)
            {
                case LoginMessage.ID:
                    result = new LoginMessage(client, jsonObject);
                    break;
                case PlayerCardsMessage.ID:
                    result = new PlayerCardsMessage(client, jsonObject);
                    break;
                default:
                    Output.LogError(TAG, "Message not found");
                    break;
            }
            return result;
        }
        protected JObject Json { get; private set; }
        protected Client Client { get; private set; }
        public int Id { get; private set; }

        public DefaultMessage(Client client, int id, JObject json)
        {
            Client = client;
            Id = id;
            Json = json;
        }

        public abstract MessageModelDefault? Deserialized();
        public abstract MessageModelDefault Serialized();
    }
}
