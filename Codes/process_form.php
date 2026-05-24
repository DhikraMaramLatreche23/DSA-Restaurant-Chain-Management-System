<?php
if ($_SERVER['REQUEST_METHOD'] === 'POST') {
    // Retrieve form data
    $restaurantName = $_POST['restaurantName'];
    $ownership = $_POST['ownership'];
    $numEmployees = $_POST['numEmployees'];
    $wilaya = $_POST['wilaya'];
    $district = $_POST['district'];
    $city = $_POST['city'];
    $establishmentDate = $_POST['establishmentDate'];

    // Create CSV row
    $csvRow = "$restaurantName,$ownership,$numEmployees,$wilaya,$district,$city,$establishmentDate";

    // Append to CSV file
    file_put_contents('dba.csv', $csvRow . PHP_EOL, FILE_APPEND );

    // You can add additional logic or validation here if needed

    echo 'done';
}
?>
