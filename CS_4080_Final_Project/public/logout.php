<?php
session_start(); // Starts session to manage user state
session_unset(); // Clear all session variables
session_destroy(); // Destroy session, logging out user (Chapter 5: Scope management)
header("Location: index.php"); // Redirect to homepage after logout
exit;
?>
