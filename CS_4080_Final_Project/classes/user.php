<?php
require_once '../config/config.php';

class User {
    private $db; // Private database connection

    public function __construct() {
        $this->db = getDbConnection(); // DB connection
    }

    public function register($username, $password) {
        if ($this->checkUsernameExists($username)) {
            return false;
        }

        $hashedPassword = password_hash($password, PASSWORD_BCRYPT);
        /* 3 --- password_hash()
            Used to securely hash and salt the user's password before storing it in the database.
            ( Hash + Salt example: ("pass" + "qO76sMnu") = 77b177de23f81d37b5b4495046b227befa4546db63cfe6fe541fc4c3cd216eb9 )
        */
        $stmt = $this->db->prepare("INSERT INTO users (username, password) VALUES (?, ?)");
        $stmt->bind_param("ss", $username, $hashedPassword);
        return $stmt->execute();
    }

    public function authenticate($username, $password) {
        $stmt = $this->db->prepare("SELECT password FROM users WHERE username = ?");
        $stmt->bind_param("s", $username);
        $stmt->execute();
        $stmt->bind_result($hashedPassword);
        $stmt->fetch();

        if (password_verify($password, $hashedPassword)) { 
            /* 3 --- password_verify()
                Used to check if the provided password matches the stored hashed password during login.
            */
            $_SESSION['username'] = $username; 
            return true;
        }
        return false;
    }

    // Checks if a username already exists
    public function checkUsernameExists($username) {
        $stmt = $this->db->prepare("SELECT id FROM users WHERE username = ?");
        $stmt->bind_param("s", $username);
        $stmt->execute();
        $stmt->store_result();
        return $stmt->num_rows > 0;
    }

    // Verifies if the given current password matches the stored password for a user
    public function verifyPassword($username, $currentPassword) {
        $stmt = $this->db->prepare("SELECT password FROM users WHERE username = ?");
        $stmt->bind_param("s", $username);
        $stmt->execute();
        $stmt->bind_result($hashedPassword);
        $stmt->fetch();
        return password_verify($currentPassword, $hashedPassword);
    }

    // Updates the password for a specific user
    public function updatePassword($username, $newPassword) {
        $hashedPassword = password_hash($newPassword, PASSWORD_BCRYPT);
        $stmt = $this->db->prepare("UPDATE users SET password = ? WHERE username = ?");
        $stmt->bind_param("ss", $hashedPassword, $username);
        return $stmt->execute();
    }
}
?>
