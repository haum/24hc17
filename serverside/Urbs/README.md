# Urbs Server for 24hc17 HAUM's subject

This is the full code of the Urbs server in the same state as at the end of the 24h of
code contest.

## Install and run

Urbs is based on [Django](https://www.djangoproject.com/) and is preferably ran in a
virtual environnement with Python 3.5/3.6.

### Setup the virtualenv

Be sure to use the **Python3** version of pip (particularly on Debian-based distros):

	# pip install virtualenv
	$ virtualenv -ppython3 .venv
	$ source .venv/bin/activate
	$ pip install -r requirements.txt

### Create the database and static dir

	$ source .venv/bin/activate
	$ ./manage.py migrate
	$ ./manage.py createsuperuser
	$ ./manage.py collectstatic

To load the dataset of Challenges, Steps and Anims used during the 24h:

	$ source .venv/bin/activate
	$ ./manage.py loaddata fixtures/teams_steps_anims.json

### Run the server

	$ source .venv/bin/activate
	$ ./manage.py runserver

Then go to http://localhost:8000/admin

To serve through Apache, use the following config and be sure to add your vhost's
ServerName in `ALLOWED_HOSTS`:

	<VirtualHost *:80>
		ServerName example.com

		ServerAdmin master@example.com

		WSGIScriptAlias / /path/to/Urbs/Urbs/wsgi.py
		WSGIDaemonProcess UrbsServer python-path=/path/to/Urbs/:/path/to/Urbs/.venv/lib/<your_python_version>/site-packages/ processes=2 threads=15
		WSGIProcessGroup UrbsServer

		Alias /static/ /path/to/Urbs/static/

		<Directory /path/to/Urbs/>
		<Files wsgi.py>
			Require all granted
		</Files>
		</Directory>

		<Directory /path/to/Urbs/static/>
			Require all granted
		</Directory>

		ErrorLog ${APACHE_LOG_DIR}/Urbs.error.log
		CustomLog ${APACHE_LOG_DIR}/Urbs.access.log combined

	</VirtualHost>

Note that it also requires `mod_wsgi`.
