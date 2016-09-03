#!/usr/bin/env python

# ----------- bibliotecas utilizadas
import sys
import tweepy
import os
import os.path
import datetime
import serial
import thread
from tweepy.utils import import_simplejson

# -------- Chaves obtidas no site (omitidas aqui por questões de segurança)
CONSUMER_KEY = '****************************' 
CONSUMER_SECRET = '*****************************'
ACCESS_KEY = ******************************'
ACCESS_SECRET = '*********************************
potencia=''

#---- abrir porta serial
ser = serial.Serial('/dev/tty.usbmodem1431') 
#--- verificar se a porta está sendo utilizada ou não
print ser.portstr       

# --- Configuração da conexão com o servidor
json = import_simplejson()
auth = tweepy.OAuthHandler(CONSUMER_KEY, CONSUMER_SECRET)
auth.set_access_token(ACCESS_KEY, ACCESS_SECRET)
api = tweepy.API(auth)


#--- Classe de monitoramento do servidor
class CustomStreamListener(tweepy.StreamListener):
    def on_status(self, status):
        print status.text
        print status.user.screen_name

#---Controle de acionamento da lâmpada para ligar
        if (status.text.find('@CasaOrientada Ligar')!=-1 and status.user.screen_name == 'rorizvitor'):
            potencia = status.text[21]
            ser.write(potencia)
            print potencia
 
#---Controle de ativação do alarme  
        if (status.text.find('@CasaOrientada Ativar alarme')!=-1 and status.user.screen_name == 'rorizvitor'):
            ser.write('7')

#---Controle de desativação do alarme 
        if (status.text.find('@CasaOrientada Desativar alarme')!=-1 and status.user.screen_name == 'rorizvitor'):
            ser.write('8')

#---Controle de acionamento da lâmpada para desligar         
        if (status.text.find('@CasaOrientada Apagar')!=-1 and status.user.screen_name == 'rorizvitor'):
            potencia = '0'
            ser.write(potencia)
            print potencia

    def on_error(self, status_code):
        print >> sys.stderr, 'Encountered error with status code:', status_code
        return True # Don't kill the stream

    def on_timeout(self):
        print >> sys.stderr, 'Timeout...'
        return True # Don't kill the stream
    
#--- Função que monitora o servidor utilizando a classe criada acima
sapi = tweepy.streaming.Stream(auth, CustomStreamListener())

#--- filtro de captação da palavra chave
def filtro():
    sapi.filter(track=['@CasaOrientada'])
def serial_monitor():
    while 1:
        
        #leitura = ser.read()

#- Se receber este caracter via serial (do arduino), atualiza status da casa   
        if ser.read() == 'R':
            print 'Invasao'
            api.update_status('Sua casa foi invadida em '+str(datetime.datetime.now()))
            #leitura = ''

#--- Treads de monitoramento do servidor e da serial, repectivamente
try:
   thread.start_new_thread(filtro,())
   thread.start_new_thread(serial_monitor,())
except:
   print "Error: unable to start thread"

while 1:
   pass
