#!/usr/bin/python

# Checks for email over IMAP.

import getpass, imaplib, os, email, re, time, serial

# Arduino Location - look bottom right corner of arduino window
#arduino_Location = ''

#ser = serial.Serial(arduino_Location)

# insert the words that you want to check for
words = ['alerts@cloudmonitoring.rackspace.com']

#how many emails to go through when searching
#negative number to go from beginning of list
emailHistory = -10

# email information
#==================================================
#==================================================
#Required
userName = ''
passWord = ''
#==================================================
#==================================================


class emailSearch(object):
	"""docstring for emailSearch"""
	def __init__(self):
		super(emailSearch, self).__init__()

		# login in to email account
		self.m = imaplib.IMAP4_SSL("imap.gmail.com")
		#replace raw inputs with your credentials as string to automate
		self.m.login(userName, passWord)
		# change to select different inbox
		self.m.select("INBOX")

	# checks for word in email Subject and From fields
	def findWholeWord(self, w):
		"""Search string with another string
		call as: findWholeWord(search for)(search in)"""
		return re.compile(r'\b({0})\b'.format(w), flags=re.IGNORECASE).search

	# functino to search email against strings
	def searchEmail(self):
		self.m.select("INBOX")

		#UNCOMMENT this line to only search unread emails
		# typ, data = self.m.search(None, "(UNSEEN)")
		typ, data = self.m.search(None, "ALL")

		# actual checking
		for num in data[0].split()[emailHistory:]:
			typ, data = self.m.fetch(num, "(BODY.PEEK[HEADER.FIELDS (FROM SUBJECT)])")
			for word in words:
				if self.findWholeWord(word)(data[0][1]) != None:
					# something has been found
					# uncomment line to write to arduino here
					# ser.write('')
					print "We found %s in \n %s" % (word, data[0][1])
					time.sleep(10)


		
def main():
	email = emailSearch()
	while True:
		email.searchEmail()
		# change time to wait longer between checks
		# given in seconds
		time.sleep(2)

if __name__ == '__main__':
	main()