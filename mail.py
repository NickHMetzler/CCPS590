import smtplib
from email.mime.multipart import MIMEMultipart
from email.mime.base import MIMEBase
from email.mime.text import MIMEText
from email import encoders

# use PORT 587 not 465 
PORT = 587  # For SSL
# GMail server
SERVER = "smtp.gmail.com"

#Email Address and Password
send_from = "ccps706testeremail@gmail.com"
password = "Sattar706"

#Email address to send to
send_to = "nickfromportugal@gmail.com"  # Enter receiver address

#Subject message and files
subject = "You Didn't Say the Magic Word!"
text = "Hello"
files = "MagicWord.gif"

# save user/pw info in .env in same dir
from dotenv import load_dotenv
load_dotenv()

def send_mail(send_from,send_to,subject,text,files,username='',password='',isTls=True):
    msg = MIMEMultipart()
    msg['From'] = send_from
    msg['To'] = send_to
    msg['Subject'] = subject
    msg.attach(MIMEText(text))
    
    part = MIMEBase('application', "octet-stream")
    if(files != ''):
        part.set_payload(open(files, "rb").read())
        encoders.encode_base64(part)
        part.add_header('Content-Disposition', 'attachment; filename=' + files)
        msg.attach(part)
    
    smtp = smtplib.SMTP(SERVER, PORT)
    if isTls:
        smtp.starttls()
    smtp.login(username,password)
    smtp.sendmail(send_from, send_to, msg.as_string())
    print("Success: Email sent!")
    smtp.quit()




# main driver
if __name__ == '__main__':
    # send the email with csv file attachment from same dir ('im.csv')
    print("Attempting to send email from: ", send_from,"\nwith subject:", subject, "\nwith text:", text, "\nand file:", files, "\nto email:", send_to)
    send_mail(send_from,send_to,subject,text,files,username=send_from,password=password,isTls=True)
