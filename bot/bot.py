import pydle
import encodedState
import requests
import json

chan = '#test24'
admins = ['seb_vallee', 'matael', 'jackdesbwa']
botname = 'Vitellius'
botpasswd = 'vincentjousse'
realname = 'NeroBot'
domain = 'http://24hc17.haum.org/api/'

class NeroBot(pydle.Client):

    team = ''

    def on_connect(self):
        self.message('nickserv', 'IDENTIFY ' + botname + ' ' + botpasswd)
        print('IDENTIFY ' + botname + ' ' + botpasswd)
        self.join(chan)

    def on_join(self, channel, player):
        if player not in admins and player != botname:
            team = self.get_team(player)
            if not team and player != botname:
                self.message(channel, player + ": Hi stranger! Please answer my question in private !")
                self.message(player, "Hi stranger, " + player + "! What's your team's name ? (begin your reply with 'team:')")
            else:
                self.message(channel, 'Hi, ' + player + "! What's going on team " + team + '?')

    def on_message(self, source, player, message):
        if (source != chan):
            if player in admins:
                self.message(chan, message)
            else:
                actualTeam = self.get_team(player)
                if message.strip().lower().startswith('team') and ":" in message:
                    if not actualTeam:
                        team = message.split(':', 1)[1].strip().replace("/", "-")
                        self.set_team(player, team)
                        self.message(player, "Understood, you're on team " + team)
                    else:
                        self.message(player, "You can't define your team twice. Please contact an admin!")
                else:
                    self.message(player, "You must speak to me on " + chan)
        else:
            team = self.get_team(player)
            if message.strip().lower().startswith(botname.lower()) and ":" in message:
                token = message.split(':', 1)[1].strip()
                newtoken = self.send_token(player, token)
                if not newtoken:
                    self.message(chan, "Did you try to fool me, " + player + "?")
                else:
                    if newtoken == "Habemus victorem":
                        self.message(chan, "We have a winner ! Please applause team " + team + " !")
                    else:
                        self.message(chan, "If you were right " + player + ", the token to continue your journey is : " + newtoken)

    def on_part(self, channel, player, message):
        print(player + ' leave the channel !')

    def on_nick_change(self, old, new):
        if old != botname:
            print(old + " change his/her nick to " + new)

    def get_api(self, endpoint):
        print(endpoint)
        r = requests.get(endpoint)
        if (r.status_code == requests.codes.ok):
            return r.json()
        return False

    def get_team(self, player):
        data = self.get_api(domain + 'user/' + player)
        if data :
            return data['result'][0]['team']['name']
        else:
            return False

    def set_team(self, player, team):
        ok = self.get_api(domain + 'team/' + team + '/adduser/' + player)
        if not ok:
            return False
        return True

    def send_token(self, player, token):
        data = self.get_api(domain + 'token/' + player + '/' + token)
        if not data:
            return False
        else:
            if data['status'] == 'valid token':
                return data['result']['next']['token']
            elif data['status'] == "Habemus victorem":
                return "Habemus victorem"
            else:
                return data


client = NeroBot(botname, realname=realname)
client.connect('irc.freenode.net', 6697, tls=True, tls_verify=False)
client.handle_forever()
