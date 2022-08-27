<?php
$servername = "localhost";
$username = "harishid_iot";
$password = "harisganteng";
$dbname = "harishid_iot";
$id  = $_GET['id'];
$idset = (int) $id;
// Create connection
$conn = new mysqli($servername, $username, $password, $dbname);
// Check connection
if ($conn->connect_error) {
  echo "0";
}
else
{
  	if($idset != 0)
    {
    	$sql = "SELECT lattitude FROM gps WHERE id = ";
      	$sql .= $idset;
		$result = $conn->query($sql);

		if ($result->num_rows > 0) {
  		// output data of each row
  			while($row = $result->fetch_assoc()) {
    			echo $row["lattitude"];
        	}
		} else {
  			echo "0";
		}	
    }
}
$conn->close();

?>