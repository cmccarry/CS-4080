<?php
session_start();
require_once '../classes/Post.php';

// Check if user is logged in
if (!isset($_SESSION['username'])) {
    header("Location: login.php");
    exit;
}

$username = $_SESSION['username'];
$postObj = new Post();
$userInfo = $postObj->getUserInfo($username);
$userPosts = $postObj->getPostsByUser($username);
$error = '';
$success = '';

// Handle username change
if ($_SERVER['REQUEST_METHOD'] === 'POST' && isset($_POST['new_username'])) {
    $newUsername = $_POST['new_username'];
    
    if ($postObj->checkUsernameExists($newUsername)) {
        $error = "Username '$newUsername' is already taken.";
    } else {
        $postObj->updateUsername($username, $newUsername);
        $_SESSION['username'] = $newUsername;
        $username = $newUsername;
        $success = "Username updated successfully!";
    }
}

// Handle password change
if ($_SERVER['REQUEST_METHOD'] === 'POST' && isset($_POST['current_password'], $_POST['new_password'])) {
    $currentPassword = $_POST['current_password'];
    $newPassword = $_POST['new_password'];

    if ($postObj->verifyPassword($username, $currentPassword)) {
        $postObj->updatePassword($username, $newPassword);
        $success = "Password updated successfully!";
    } else {
        $error = "Current password is incorrect.";
    }
}
?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Profile</title>
    <link rel="stylesheet" href="assets/css/styles.css">
</head>
<body>
    <header class="masthead">
        <a href="index.php"><img src="assets/images/main_img.png" alt="Logo"></a>
        <h1>My Profile</h1>
        <nav class="nav-menu">
            <a href="index.php">Home</a>
            <a href="profile.php">Profile</a>
            <a href="new_post.php">Create New Post</a>
            <a href="logout.php">Logout</a>
        </nav>
    </header>

    <div class="container">
        <h2>Welcome, <?= htmlspecialchars($username); ?></h2>
        <p>Account created on: <?= htmlspecialchars($userInfo['created_at']); ?></p>

        <?php if ($error): ?>
            <p style="color: red;"><?= htmlspecialchars($error); ?></p>
        <?php elseif ($success): ?>
            <p style="color: green;"><?= htmlspecialchars($success); ?></p>
        <?php endif; ?>

        <form method="POST">
            <label>Change Username:</label>
            <input type="text" name="new_username" required>
            <button type="submit">Update Username</button>
        </form>

        <form method="POST">
            <h3>Change Password</h3>
            <label>Current Password:</label>
            <input type="password" name="current_password" required>

            <label>New Password:</label>
            <input type="password" name="new_password" required>
            
            <button type="submit">Update Password</button>
        </form>

        <h3>Your Posts</h3>
        <?php foreach ($userPosts as $post): ?>
            <h4><?= htmlspecialchars($post['title']); ?></h4>
            <p><?= nl2br(htmlspecialchars($post['content'])); ?></p>
            <small>Posted on <?= htmlspecialchars($post['created_at']); ?></small>
            <a href="edit_post.php?id=<?= $post['id']; ?>">Edit</a> |
            <a href="delete_post.php?id=<?= $post['id']; ?>" onclick="return confirm('Are you sure?');">Delete</a>
            <hr>
        <?php endforeach; ?>
    </div>
</body>
</html>
