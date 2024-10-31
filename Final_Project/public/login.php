<?php
session_start(); // Starts the session to track user login state (Chapter 5: Scope)
require_once '../classes/User.php';

$userObj = new User(); // Object for managing user-related functions (Chapter 11: Encapsulation)

if ($_SERVER['REQUEST_METHOD'] === 'POST') { // Check if form was submitted
    // Attempt to authenticate user
    if ($userObj->authenticate($_POST['username'], $_POST['password'])) { // Encapsulated authentication method
        header("Location: index.php"); // Redirect to homepage on successful login
        exit;
    } else {
        $error = "Invalid username or password."; // Display error if login fails
    }
}
?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Login</title>
    <link rel="stylesheet" href="assets/css/styles.css">
</head>
<body>
    <header class="masthead">
        <a href="index.php"><img src="assets/images/main_img.png" alt="Logo"></a>
        <h1>Login</h1>
        <nav class="nav-menu">
            <a href="index.php">Home</a>
        </nav>
    </header>

    <div class="container">
        <h2>Login</h2>

        <!-- Display error message if login fails -->
        <?php if (isset($error)): ?>
            <p style="color: red;"><?= htmlspecialchars($error); ?></p>
        <?php endif; ?>

        <!-- Login form -->
        <form method="POST">
            <label>Username:</label>
            <input type="text" name="username" required>

            <label>Password:</label>
            <input type="password" name="password" required>
            
            <button type="submit">Login</button>
        </form>

        <p>Don't have an account? <a href="register.php">Create Account</a></p>
    </div>
</body>
</html>
