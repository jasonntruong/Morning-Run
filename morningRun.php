<html>
	<head>
		<link rel="stylesheet" type="text/css" href="styles.css">
	</head>
	
	<body>
		<h1>Morning Run</h1>
		
		<div>

			<!-- Buttons that send GET requests 
				 My ESP32 modules send the same GET requests
				(for debugging purposes since connecting 4 ESP32 modules is a lot of work)
			-->

			<h2>Button Simulators</h2>

			<form method="get" action="morningrun.php">
				<input id="button1" type="submit" name="REQ_ALARM" value="1"/>
			</form>

			<form method="get" action="morningrun.php">
				<input id="button2" type="submit" name="REQ_ALARM" value="2"/>
			</form>

			<form method="get" action="morningrun.php">
				<input id="button3" type="submit" name="REQ_ALARM" value="3"/>
			</form>

			<form method="get" action="morningrun.php">
				<input id="button4" type="submit" name="REQ_ALARM" value="4"/>
			</form>
		</div>

	</body>

</html>


<?php

	ini_set('display_errors', true);
	error_reporting(E_ALL & ~E_NOTICE);

	function addToDB($number) {
		# adds $number to SQL Database to track what GET requests are recieved from my ESP32 modules. (useful for debugging purposes)

		$servername = "SERVERNAME";
		$username = "USERNAME";		#no, this is not my actual servername, username, and password
		$password = "PASSWORD";
		$databaseName="alarmDB";

		$connection = new mysqli($servername, $username, $password, $databaseName);

		if ($connection->connect_error) {
			echo "Connection error";
			die("Connection failed: " . $connection->connect_error);
		}

		$sql = "INSERT INTO alarmNum (alarmVal)
		VALUES ('$number')";

		if ($connection->query($sql) === TRUE) {
			echo "Data added success";
		}
		else {
			echo "Error" . $connection->error;
		}
		@$connection->close;
	}

	if (isset($_GET['REQ_ALARM'])) {	#REQ_ALARM is the GET request name

		$REQ_ALARM = $_GET['REQ_ALARM'];
		$REQ_NUM = file_get_contents("reqnum.txt");		#reads the number in reqnum.txt, which is a randomized number from 1-4 (randomnum.py file randomizes this)
		$REQ_NUM = str_replace(' ','', $REQ_NUM);

		

		if (strcmp(substr($REQ_NUM,0,1), $REQ_ALARM) == 0) {	#if GET request number == reqnum.txt number, stop the alarm by restarting the Raspberry Pi
			addToDB("TURN_OFF_ALARM" . $REQ_ALARM . "WORKS");
			echo exec("sudo reboot");
		}
		
		else {
			addToDB("TURN_OFF_ALARM" . $REQ_ALARM);
		}
	}


?>