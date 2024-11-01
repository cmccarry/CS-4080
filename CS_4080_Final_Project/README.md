# CS 4080 Project: Blog Website

This project is a simple blog website built using PHP and MySQL. Users can create accounts, log in, write blog posts, and comment on each other’s posts. The project demonstrates fundamental web development concepts, including user authentication, CRUD operations, and relational database handling in MySQL.


## Project Features

- **User Authentication**: Users can register, log in, and log out securely.
- **Blog Posts**: Logged-in users can create, edit, and delete their own blog posts.
- **Comments**: Users can comment on any post and delete their own comments.
- **User Profiles**: Each user has a profile page displaying their posts and comments, along with options to change their username and password.
- **Pagination and Filtering**: Blog posts are paginated for easier browsing, and users can filter posts by author.
- **Responsive Design**: The website layout is styled with CSS to be responsive and user-friendly.


## Requirements

- **XAMPP** (or any compatible PHP and MySQL environment)
- **Web Browser** (e.g., Chrome, Firefox)


## Installation and Setup

### 1. Set Up the Database

1. Start **XAMPP** and ensure both **Apache** and **MySQL** are running.
2. Open **phpMyAdmin** by navigating to `http://localhost/phpmyadmin`.
3. Import the database setup file:
   - Go to the **Import** tab.
   - Select `cs_4080_project_db_setup.sql` from the `sql/` folder.
   - Click **Go** to create the database and tables.

### 2. Configure Database Connection (if needed)

1. Open the `config/config.php` file in a code editor.
2. Update the database credentials (default username is `root` with an empty password in XAMPP):

   ```php
   $servername = "localhost";
   $username = "root";
   $password = ""; // Add your password here if set
   $dbname = "cs_4080_project_db";
   ```

### 3. Place the Project in the XAMPP Directory

1. Move the CS_4080_Final_Project folder to the htdocs directory within your XAMPP installation.

    Example path: `C:\\xampp\\htdocs\\CS_4080_Final_Project`

### 4. Run the Project

1. Open a web browser and navigate to the homepage:
    
    `http://localhost/CS_4080_Final_Project/public/index.php`

2. You can now:

    - Register a new user.
    - Log in to create posts and comments.
    - Access your profile to manage your posts and comments.


## Usage Guide
- **Homepage**: Use `index.php` to view all posts, filter by author, and comment on posts.
- **Register and Login**: Use `register.php` to create an account and `login.php` to log in.
- **Profile**: Use `profile.php` to view and edit your posts and comments and update your username and password.
- **Create and Edit Posts**: Use `new_post.php` to create a post, and `edit_post.php` to modify an existing one.
- **Logout**: Use `logout.php` to log out of your account.