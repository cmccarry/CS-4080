<?php
session_start(); // Starts session to manage user state
session_unset(); // Clear all session variables used
session_destroy(); // Destroy session, logging out user
header("Location: index.php"); // Redirect to homepage after logout
exit;
?>
