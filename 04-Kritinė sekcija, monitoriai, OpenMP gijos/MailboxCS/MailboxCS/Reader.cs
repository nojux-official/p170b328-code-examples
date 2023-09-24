using System.Collections.Generic;

namespace MailboxCS
{
    public class Reader
    {
        public List<int> Letters { get; }
        private readonly MailBox _mailbox;
        private readonly int _id;
        private readonly int _terminateMessage;

        public Reader(int terminateMessage, MailBox mailbox, int id)
        {
            _mailbox = mailbox;
            _id = id;
            Letters = new List<int>();
            _terminateMessage = terminateMessage;
        }

        public void Read()
        {
            while (true)
            {
                var message = _mailbox.Get(_id);
                if (message == _terminateMessage)
                {
                    break;
                }
                Letters.Add(message);
            }
        }
    }
}