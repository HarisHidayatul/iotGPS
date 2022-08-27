<?php
	$servername = "localhost";
	$username = "harishid_iot";
	$password = "harisganteng";
	$dbname = "harishid_iot";
	$lat = $_GET['lat'];
	$lng = $_GET['lng'];
	$id  = $_GET['id'];
	$lngset = (float) $lng;
	$latset = (float) $lat;
	$idset  = (int) $id;
	if($idset != 0)
    {
      if(($latset != 0)&&($lngset != 0))
      {			
        // Create connection
		$conn = new mysqli($servername, $username, $password, $dbname);
		// Check connection
		if ($conn->connect_error) {
		  die("Connection failed: " . $conn->connect_error);
		}
		$sql = "UPDATE gps SET lattitude=";
        $sql .= $latset;
        $sql .= ", longtitude=";
        $sql .= $lngset;
        $sql .= " WHERE id=";
        $sql .= $idset;
        if ($conn->query($sql) === TRUE) {
		  echo "New record created successfully";
		} else {
		  echo "Error: " . $sql . "<br>" . $conn->error;
		}

		$conn->close();
      }
    }
?>