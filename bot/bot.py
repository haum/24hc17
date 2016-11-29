from subprocess import check_output, STDOUT
import pydle

chan = '#testsvallee'
admins = ['seb_vallee', 'matael']
tokenbin = './increment_token'
botname = 'Imperator'
realname = 'NeroBot'

class NeroBot(pydle.Client):

    def on_connect(self):
         self.join(chan)

    def on_message(self, source, player, message):
        if (source != chan):
            self.message(player, "You must speak to me on " + chan)
        else:
            if message.strip().lower().startswith('token') and ":" in message:
                token = message.split(':', 1)[1].strip()
                for dest in admins:
                    self.message(dest, "ADMIN : " + player + " has tried the token : " + token)

                output = check_output([tokenbin, token], stderr=STDOUT, shell=False)
                teamid = output.decode().split("\n")[1].split("=", 1)[1]
                riddle = output.decode().split("\n")[2].split("=", 1)[1]
                faults = output.decode().split("\n")[3].split("=", 1)[1]
                newtoken = output.decode().split("\n")[5]
                self.message(chan, "If you were right " + player + ", the token to continue your journey is : " + newtoken)
            #else:
                #self.message(chan, "I expect more from you, " + player + "!")

client = NeroBot(botname, realname=realname)
client.connect('irc.freenode.net', 6697, tls=True, tls_verify=False)
client.handle_forever()
