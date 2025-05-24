package atelier.atelier_de_origami.repository.database;

import atelier.atelier_de_origami.domain.Teacher;
import atelier.atelier_de_origami.repository.ITeacherRepo;
import atelier.atelier_de_origami.utils.JdbcUtils;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.util.ArrayList;
import java.util.List;
import java.util.Optional;
import java.util.Properties;

public class TeacherRepo implements ITeacherRepo {

    private JdbcUtils dbUtils;
    private static final EncryptUtils encryptUtils = new EncryptUtils();

    public TeacherRepo(Properties props){
        dbUtils = new JdbcUtils(props);
    }

    @Override
    public void save(Teacher teacher) {
        Connection conn = dbUtils.getConnection();
        try (PreparedStatement preStmt = conn.prepareStatement("insert into teacher (firstname, lastname, age, username, password) values (?, ?, ?, ?, ?)")) {
            preStmt.setString(1, teacher.getFirstname());
            preStmt.setString(2, teacher.getLastname());
            preStmt.setInt(3, teacher.getAge());
            preStmt.setString(4, teacher.getUsername());
            preStmt.setString(5, encryptUtils.encrypt1(teacher.getPassword()));
            preStmt.executeUpdate();
        } catch (Exception e) {
            System.out.println("Error DB " + e);
        }
    }

    @Override
    public Teacher findByUsername(String username) {
        Connection conn = dbUtils.getConnection();
        try (PreparedStatement preStmt = conn.prepareStatement("select * from teacher where username = ?")) {
            preStmt.setString(1, username);
            try (ResultSet result = preStmt.executeQuery()) {
                if (result.next()) {
                    Integer id = result.getInt("id");
                    String firstname = result.getString("firstname");
                    String lastname = result.getString("lastname");
                    int age = result.getInt("age");
                    String password = encryptUtils.decrypt1(result.getString("password"));
                    Teacher teacher = new Teacher(id, firstname, lastname, age, username, password);
                    return teacher;
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
        try(PreparedStatement preStmt = conn.prepareStatement("select * from teacher where id = ?")){
            preStmt.setInt(1, integer);
            try(ResultSet result = preStmt.executeQuery()){
                if(result.next()){
                    Integer id = result.getInt("id");
                    String firstname = result.getString("firstname");
                    String lastname = result.getString("lastname");
                    int age = result.getInt("age");
                    String username = result.getString("username");
                    String password = encryptUtils.decrypt1(result.getString("password"));
                    Teacher teacher = new Teacher(id, firstname, lastname, age, username, password);
                    return Optional.of(teacher);
                }
            }
        } catch (Exception e) {
            System.out.println("Error DB " + e);
        }
        return Optional.empty();
    }

    @Override
    public Iterable<Teacher> findAll() {
        Connection conn = dbUtils.getConnection();
        List<Teacher> teachers = new ArrayList<>();
        try(PreparedStatement preStmt = conn.prepareStatement("select * from teacher")) {
            try (ResultSet result = preStmt.executeQuery()) {
                while (result.next()) {
                    Integer id = result.getInt("id");
                    String firstname = result.getString("firstname");
                    String lastname = result.getString("lastname");
                    int age = result.getInt("age");
                    String username = result.getString("username");
                    String password = encryptUtils.decrypt1(result.getString("password"));
                    Teacher teacher = new Teacher(id, firstname, lastname, age, username, password);
                    teachers.add(teacher);
                }
            }
        } catch (Exception e) {
            System.out.println("Error DB " + e);
        }
        return teachers;
    }
}
