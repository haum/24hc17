from subprocess import check_output, STDOUT
import pydle
import encodedState

chan = '#testsvallee'
admins = ['seb_vallee', 'matael']
botname = 'Imperator'
realname = 'NeroBot'

class NeroBot(pydle.Client):

    def on_connect(self):
         self.join(chan)
         self.ec = encodedState.EncodedState()

    def on_message(self, source, player, message):
        if (source != chan):
            self.message(player, "You must speak to me on " + chan)
        else:
            if message.strip().lower().startswith('token') and ":" in message:
                token = message.split(':', 1)[1].strip()
                for dest in admins:
                    self.message(dest, "ADMIN : " + player + " has tried the token : " + token)
                self.ec.from_string(token)
                for dest in admins:
                    self.message(dest, "ADMIN : " + player + " got : " + self.ec.print_var())
                #self.message(chan, "If you were right " + player + ", the token to continue your journey is : " + newtoken)

client = NeroBot(botname, realname=realname)
client.connect('irc.freenode.net', 6697, tls=True, tls_verify=False)
client.handle_forever()
