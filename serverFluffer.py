# Checks for email over IMAP.

import getpass, imaplib, os, email, re, time, serial

words = ['alerts@cloudmonitoring.rackspace.com']

def findWholeWord(w):
	return re.compile(r'\b({0})\b'.format(w), flags=re.IGNORECASE).search

def searchEmail():
	m = imaplib.IMAP4_SSL("imap.gmail.com")
	# m.login('michaeldjeffrey', 'migpok35')
	m.login(raw_input("Username:"), raw_input("password:"))
	m.select("INBOX")
	# typ, data = m.search(None, "(UNSEEN)")
	typ, data = m.search(None, "ALL")
	for num in data[0].split()[-10:]:
		typ, data = m.fetch(num, "(BODY.PEEK[HEADER.FIELDS (FROM SUBJECT)])")
		for word in words:
			if findWholeWord(word)(data[0][1]) != None:
				print "We found %s in \n %s" % (word, data[0][1])
				time.sleep(10)
	m.close()
	m.logout()

m = imaplib.IMAP4_SSL("imap.gmail.com")
m.login(raw_input("Username:"), raw_input("password:"))
m.select("INBOX")
	
while True:
	searchEmail()
	print 'hello'
	time.sleep(2)



