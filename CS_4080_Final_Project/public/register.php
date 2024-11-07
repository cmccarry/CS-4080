<?php
require_once '../classes/User.php';

$userObj = new User();
$error = '';

if ($_SERVER['REQUEST_METHOD'] === 'POST') { // Handles form submission
    if ($userObj->register($_POST['username'], $_POST['password'])) {
        echo "Account created successfully! <a href='login.php'>Log in</a>";
    } else {
        $error = "Error: Username already exists. Please choose a different username."; // Error if username taken
    }
}
?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Register</title>
    <link rel="stylesheet" href="assets/css/styles.css">
</head>
<body>
    <header class="masthead">
        <a href="index.php"><img src="assets/images/main_img.png" alt="Logo"></a>
        <h1>Register</h1>
        <nav class="nav-menu">
            <a href="index.php">Home</a>
        </nav>
    </header>

    <div class="container">
        <h2>Register</h2>
        
        <?php if ($error): ?>
            <p style="color: red;"><?= htmlspecialchars($error); ?></p>
        <?php endif; ?>

        <form method="POST">
            <label>Username:</label>
            <input type="text" name="username" required>
            <label>Password:</label>
            <input type="password" name="password" required>
            <button type="submit">Create Account</button>
        </form>
    </div>
</body>
</html>
