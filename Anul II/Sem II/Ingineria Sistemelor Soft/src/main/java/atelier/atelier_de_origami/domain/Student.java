package atelier.atelier_de_origami.domain;

import jakarta.persistence.Column;
import jakarta.persistence.Table;
import jakarta.validation.constraints.*;

@jakarta.persistence.Entity
@Table(name = "student")
public class Student extends Entity<Integer> {

    @Column(name = "firstname")
    @NotBlank(message = "First name is required")
    @Size(max = 50, message = "First name must be ≤ 50 characters")
    private String firstname;

    @Column(name = "lastname")
    @NotBlank(message = "Last name is required")
    @Size(max = 50, message = "Last name must be ≤ 50 characters")
    private String lastname;

    @Column(name = "age")
    @Min(value = 6, message = "Age must be at least 6")
    @Max(value = 120, message = "Age must be ≤ 120")
    private int age;

    @Column(name = "phonenumber")
    @Pattern(regexp = "^\\+?[0-9\\s-]{6,15}$",
             message = "Invalid phone number (e.g., +1234567890 or 123-456-7890)")
    private String phoneNumber;

    @Column(name = "email")
    @Email(message = "Email must be valid (e.g., user@example.com)")
    @NotBlank(message = "Email is required")
    private String email;

    @Column(name = "username")
    @NotBlank(message = "Username is required")
    @Size(max = 50, message = "Username must be ≤ 50 characters")
    private String username;

    @Column(name = "password")
    @NotBlank(message = "Password is required")
    @Size(min = 4, message = "Password must be between >= 4 characters")
    private String password;

    public Student() {
    }

    public Student(int id, String firstname, String lastname, int age, String phoneNumber, String email, String username, String password) {
        setId(id);
        this.firstname = firstname;
        this.lastname = lastname;
        this.age = age;
        this.phoneNumber = phoneNumber;
        this.email = email;
        this.username = username;
        this.password = password;
    }

    public Student(String firstname, String lastname, int age, String phoneNumber, String email, String username, String password) {
        this.firstname = firstname;
        this.lastname = lastname;
        this.age = age;
        this.phoneNumber = phoneNumber;
        this.email = email;
        this.username = username;
        this.password = password;
    }

    public String getFirstname() {
        return firstname;
    }
    public String getLastname() {
        return lastname;
    }
    public int getAge() {
        return age;
    }
    public String getPhoneNumber() {
        return phoneNumber;
    }
    public String getEmail() {
        return email;
    }
    public String getUsername() {
        return username;
    }
    public String getPassword() {
        return password;
    }

    public void setFirstname(String firstname) {
        this.firstname = firstname;
    }
    public void setLastname(String lastname) {
        this.lastname = lastname;
    }
    public void setAge(int age) {
        this.age = age;
    }
    public void setPhoneNumber(String phoneNumber) {
        this.phoneNumber = phoneNumber;
    }
    public void setEmail(String email) {
        this.email = email;
    }
    public void setUsername(String username) {
        this.username = username;
    }
    public void setPassword(String password) {
        this.password = password;
    }
}
