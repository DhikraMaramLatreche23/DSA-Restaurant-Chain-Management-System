<?php
error_reporting(E_ALL);
ini_set('display_errors', 1);

if ($_SERVER['REQUEST_METHOD'] === 'POST') {
    // Retrieve form data
    $day = $_POST['day'];
    $Algerian_sales = $_POST['Algerian_sales'];
    $Indian_sales = $_POST['Indian_sales'];
    $Chinese_sales = $_POST['Chinese_sales'];
    $Syrian_sales = $_POST['Syrian_sales'];
    $Europ_sales = $_POST['Europ_sales'];
    $id_rest = $_POST['id_rest'];
    $rent = $_POST['rent'];
    $employees = $_POST['employees'];
    $electricity = $_POST['electricity'];
    $gas = $_POST['gas'];
    $vegetables = $_POST['vegetables'];
    $meats = $_POST['meats'];
    $otherIngredients = $_POST['otherIngredients'];
    $publicity = $_POST['publicity'];
    $other = $_POST['other'];

    // Create CSV row
    $csvRow = "$id_rest,$day,$Algerian_sales,$Indian_sales,$Chinese_sales,$Syrian_sales,$Europ_sales,$rent,$employees,$electricity,$gas,$vegetables,$meats,$otherIngredients,$publicity,$other";

    // Append to CSV file
    file_put_contents('dbaforSalesCosts.csv', $csvRow . PHP_EOL, FILE_APPEND);

    // Execute your C++ program
    $cppResult = shell_exec('RcmsSystemBST.cpp');

    // You can check $cppResult if needed
    echo json_encode(array('success' => true, 'message' => 'Form submitted successfully', 'cpp_result' => $cppResult));
} else {
    // Respond with error if not a POST request
    echo json_encode(array('success' => false, 'message' => 'Invalid request method'));
}
?>
