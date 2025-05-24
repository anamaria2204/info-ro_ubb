package atelier.atelier_de_origami.domain;

import jakarta.persistence.Column;
import jakarta.persistence.Table;
import jakarta.validation.constraints.*;

@jakarta.persistence.Entity
@Table(name = "teacher")
public class Teacher extends Entity<Integer> {

    @Column(name = "firstname")
    @NotBlank(message = "First name is required")
    @Size(max = 50, message = "First name must be ≤ 50 characters")
    private String firstname;

    @Column(name = "lastname")
    @NotBlank(message = "Last name is required")
    @Size(max = 50, message = "Last name must be ≤ 50 characters")
    private String lastname;

    @Column(name = "age")
    @Min(value = 18, message = "Teacher must be at least 18 years old")
    @Max(value = 120, message = "Age must be ≤ 120")
    private int age;

    @Column(name = "username")
    @NotBlank(message = "Username is required")
    @Size(max = 50, message = "Username must be ≤ 50 characters")
    private String username;

    @Column(name = "password")
    @NotBlank(message = "Password is required")
    @Size(min = 4, message = "Password must be between >= 4 characters")
    private String password;

    public Teacher() {
    }

    public Teacher(int id, String firstname, String lastname, int age, String username, String password) {
        setId(id);
        this.firstname = firstname;
        this.lastname = lastname;
        this.age = age;
        this.username = username;
        this.password = password;
    }

    public Teacher(String firstname, String lastname, int age, String username, String password) {
        this.firstname = firstname;
        this.lastname = lastname;
        this.age = age;
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
    public void setUsername(String username) {
        this.username = username;
    }
    public void setPassword(String password) {
        this.password = password;
    }
}
