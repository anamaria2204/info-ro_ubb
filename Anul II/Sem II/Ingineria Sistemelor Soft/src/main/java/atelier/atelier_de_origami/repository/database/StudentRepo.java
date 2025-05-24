package atelier.atelier_de_origami.repository.database;

import atelier.atelier_de_origami.domain.Student;
import atelier.atelier_de_origami.repository.IStudentRepo;
import atelier.atelier_de_origami.utils.JdbcUtils;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.util.ArrayList;
import java.util.List;
import java.util.Optional;
import java.util.Properties;

public class StudentRepo implements IStudentRepo {

    private JdbcUtils dbUtils;
    private static final EncryptUtils encryptUtils = new EncryptUtils();

    public StudentRepo(Properties props){
        dbUtils = new JdbcUtils(props);
    }

    @Override
    public void save(Student student) {
        Connection conn = dbUtils.getConnection();
        try(PreparedStatement preStmt = conn.prepareStatement("insert into student (firstname, lastname, age, phonenumber, email, username, password) values (?, ?, ?, ?, ?, ?, ?)")){
            preStmt.setString(1, student.getFirstname());
            preStmt.setString(2, student.getLastname());
            preStmt.setInt(3, student.getAge());
            preStmt.setString(4, student.getPhoneNumber());
            preStmt.setString(5, student.getEmail());
            preStmt.setString(6, student.getUsername());
            preStmt.setString(7, encryptUtils.encrypt1(student.getPassword()));
            preStmt.executeUpdate();
        } catch (Exception e) {
            System.out.println("Error DB " + e);
        }
    }

    @Override
    public Student findByUsername(String username) {
        Connection conn = dbUtils.getConnection();
        try(PreparedStatement preStmt = conn.prepareStatement("select * from student where username = ?")){
            preStmt.setString(1, username);
            try(ResultSet result = preStmt.executeQuery()){
                if(result.next()){
                    Integer id = result.getInt("id");
                    String firstname = result.getString("firstname");
                    String lastname = result.getString("lastname");
                    int age = result.getInt("age");
                    String phoneNumber = result.getString("phonenumber");
                    String email = result.getString("email");
                    String password = encryptUtils.decrypt1(result.getString("password"));
                    Student student = new Student(id, firstname, lastname, age, phoneNumber, email, username, password);
                    return student;
                }
            }
        } catch (Exception e) {
            System.out.println("Error DB " + e);
        }
        return null;
    }

    @Override
    public Optional findOne(Integer integer) {
        Connection conn = dbUtils.getConnection();
        try(PreparedStatement preStmt = conn.prepareStatement("select * from student where id = ?")){
            preStmt.setInt(1, integer);
            try(ResultSet result = preStmt.executeQuery()){
                if(result.next()){
                    Integer id = result.getInt("id");
                    String firstname = result.getString("firstname");
                    String lastname = result.getString("lastname");
                    int age = result.getInt("age");
                    String phoneNumber = result.getString("phonenumber");
                    String email = result.getString("email");
                    String username = result.getString("username");
                    String password = encryptUtils.decrypt1(result.getString("password"));
                    Student student = new Student(id, firstname, lastname, age, phoneNumber, email, username, password);
                    return Optional.of(student);
                }
            }
        } catch (Exception e) {
            System.out.println("Error DB " + e);
        }
        return Optional.empty();
    }

    @Override
    public Iterable<Student> findAll() {
        Connection conn = dbUtils.getConnection();
        List<Student> students = new ArrayList<>();
        try(PreparedStatement preStmt = conn.prepareStatement("select * from student")) {
            try (ResultSet result = preStmt.executeQuery()) {
                while (result.next()) {
                    Integer id = result.getInt("id");
                    String firstname = result.getString("firstname");
                    String lastname = result.getString("lastname");
                    int age = result.getInt("age");
                    String phoneNumber = result.getString("phonenumber");
                    String email = result.getString("email");
                    String username = result.getString("username");
                    String password = encryptUtils.decrypt1(result.getString("password"));
                    Student student = new Student(id, firstname, lastname, age, phoneNumber, email, username, password);
                    students.add(student);
                }
            }
        } catch (Exception e) {
            System.out.println("Error DB " + e);
        }
        return students;
    }
}
