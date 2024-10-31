<?php
require_once 'Post.php'; // Include the Post class

// Instantiate the Post class to retrieve posts
$postObj = new Post();
$posts = $postObj->getAllPosts(); // Fetching all posts (Data handling)
?>

<!DOCTYPE html>
<html>
<head>
    <title>Blog Home</title>
</head>
<body>
    <h1>Blog Posts</h1>
    <?php if (count($posts) > 0): ?> <!-- Conditional check on number of posts (Chapter 8: Control Structures) -->
        <?php foreach ($posts as $post): ?> <!-- Loop through posts array (Chapter 8: Iterative Statements) -->
            <h2><?= htmlspecialchars($post['title']); ?></h2> <!-- Display post title -->
            <p><?= htmlspecialchars($post['content']); ?></p> <!-- Display post content -->
            <small>by <?= htmlspecialchars($post['author']); ?></small> <!-- Display post author -->
            <hr> <!-- Horizontal rule to separate posts -->
        <?php endforeach; ?>
    <?php else: ?>
        <p>No posts available.</p> <!-- Message if no posts are found -->
    <?php endif; ?>
</body>
</html>
