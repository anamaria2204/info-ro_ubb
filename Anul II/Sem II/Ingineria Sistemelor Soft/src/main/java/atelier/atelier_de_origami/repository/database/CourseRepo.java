package atelier.atelier_de_origami.repository.database;

import atelier.atelier_de_origami.domain.Course;
import atelier.atelier_de_origami.domain.CourseCategory;
import atelier.atelier_de_origami.domain.ExperienceLevel;
import atelier.atelier_de_origami.domain.Teacher;
import atelier.atelier_de_origami.repository.ICourseRepo;
import atelier.atelier_de_origami.repository.ITeacherRepo;
import atelier.atelier_de_origami.utils.JdbcUtils;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.util.List;
import java.util.Optional;
import java.util.Properties;

public class CourseRepo implements ICourseRepo {

    private JdbcUtils dbUtils;
    private final ITeacherRepo teacherRepo;

    public CourseRepo(Properties props, ITeacherRepo teacherRepo) {
        dbUtils = new JdbcUtils(props);
        this.teacherRepo = teacherRepo;
    }

    @Override
    public Course save(String name, LocalDateTime date, int duration, float price, CourseCategory category, Teacher teacher, ExperienceLevel experienceLevel, int maxParticipants) {
        Connection conn = dbUtils.getConnection();
        try (PreparedStatement prepStmt = conn.prepareStatement(
                "insert into course (name, date, duration, price, category, idTeacher, experiencelevel, maxparticipants) values (?, ?, ?, ?, ?, ?, ?, ?)",
                PreparedStatement.RETURN_GENERATED_KEYS)) {

            prepStmt.setString(1, name);
            DateTimeFormatter formatter = DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm:ss");
            String formattedDate = date.format(formatter);
            prepStmt.setString(2, formattedDate);
            prepStmt.setInt(3, duration);
            prepStmt.setFloat(4, price);
            prepStmt.setString(5, category.toString());
            prepStmt.setInt(6, teacher.getId());
            prepStmt.setString(7, experienceLevel.toString());
            prepStmt.setInt(8, maxParticipants);

            prepStmt.executeUpdate();
            try (ResultSet generatedKeys = prepStmt.getGeneratedKeys()) {
                if (generatedKeys.next()) {
                    int id = generatedKeys.getInt(1);
                    return new Course(id, name, date, duration, price, category, teacher, experienceLevel, maxParticipants);
                } else {
                    throw new RuntimeException("Creating course failed, no ID obtained.");
                }
            }

        } catch (Exception e) {
            System.out.println("Error DB " + e);
            return null;
        }
    }


    @Override
    public Course update(Course course, String name, LocalDateTime time, int duration, float price, CourseCategory category, ExperienceLevel experienceLevel, int maxParticipants) {
        if (course == null || course.getId() == null) {
            throw new IllegalArgumentException("Course or Course ID must not be null for update.");
        }

        Connection conn = dbUtils.getConnection();
        try (PreparedStatement prepStmt = conn.prepareStatement(
                "update course set name = ?, date = ?, duration = ?, price = ?, category = ?, experiencelevel = ?, maxparticipants = ? where id = ?")) {

            prepStmt.setString(1, name);
            DateTimeFormatter formatter = DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm:ss");
            String formattedDate = time.format(formatter);
            prepStmt.setString(2, formattedDate);
            prepStmt.setInt(3, duration);
            prepStmt.setFloat(4, price);
            prepStmt.setString(5, category.toString());
            prepStmt.setString(6, experienceLevel.toString());
            prepStmt.setInt(7, maxParticipants);
            prepStmt.setInt(8, course.getId());

            int affectedRows = prepStmt.executeUpdate();
            if (affectedRows == 0) {
                throw new RuntimeException("Update failed: no course found with id = " + course.getId());
            }

            return new Course(course.getId(), name, time, duration, price, category, course.getTeacher(), experienceLevel, maxParticipants);

        } catch (Exception e) {
            System.out.println("Error DB " + e);
            return null;
        }
    }


    @Override
    public Course delete(int id) {
        Connection conn = dbUtils.getConnection();
        Optional<Course> opt = findOne(id);
        Course course = opt.orElse(null);
        if (course != null) {
            try (PreparedStatement prepStmt = conn.prepareStatement("delete from course where id = ?")) {
                prepStmt.setInt(1, id);
                prepStmt.executeUpdate();
            } catch (Exception e) {
                System.out.println("Error DB " + e);
            }
        }
        return course;
    }

    @Override
    public Iterable<Course> findAllCourseTeacher(int idTeacher) {
        Connection conn = dbUtils.getConnection();
        List<Course> courses = new java.util.ArrayList<>();
        try(PreparedStatement preStmt = conn.prepareStatement("select * from course where idTeacher = ?")) {
            preStmt.setInt(1, idTeacher);
            try (ResultSet result = preStmt.executeQuery()) {
                while (result.next()) {
                    Integer id = result.getInt("id");
                    String name = result.getString("name");
                    String date_s = result.getString("date");
                    DateTimeFormatter formatter = DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm:ss");
                    LocalDateTime date = LocalDateTime.parse(date_s, formatter);
                    int duration = result.getInt("duration");
                    float price = result.getFloat("price");
                    CourseCategory category = CourseCategory.valueOf(result.getString("category"));
                    int id_t = result.getInt("idTeacher");
                    Optional<Teacher> teacherOpt = teacherRepo.findOne(id_t);
                    Teacher teacher = teacherOpt.orElse(null);
                    ExperienceLevel experienceLevel = ExperienceLevel.valueOf(result.getString("experiencelevel"));
                    int maxParticipants = result.getInt("maxparticipants");
                    Course course = new Course(id, name, date, duration, price, category, teacher, experienceLevel, maxParticipants);
                    courses.add(course);
                }
            }
        } catch (Exception e) {
            System.out.println("Error DB " + e);
        }
        return courses;
    }

    @Override
    public Iterable<Course> findCoursesForAge(int age) {
        return null;
    }

    @Override
    public Optional findOne(Integer integer) {
        Connection conn = dbUtils.getConnection();
        try(PreparedStatement preStmt = conn.prepareStatement("select * from course where id = ?")) {
            preStmt.setInt(1, integer);
            try(ResultSet result = preStmt.executeQuery()) {
                if(result.next()) {
                    Integer id = result.getInt("id");
                    String name = result.getString("name");
                    String date_s = result.getString("date");
                    DateTimeFormatter formatter = DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm:ss");
                    LocalDateTime date = LocalDateTime.parse(date_s, formatter);
                    int duration = result.getInt("duration");
                    float price = result.getFloat("price");
                    CourseCategory category = CourseCategory.valueOf(result.getString("category"));
                    int id_t = result.getInt("idTeacher");
                    Optional<Teacher> teacherOpt = teacherRepo.findOne(id_t);
                    Teacher teacher = teacherOpt.orElse(null);
                    ExperienceLevel experienceLevel = ExperienceLevel.valueOf(result.getString("experiencelevel"));
                    int maxParticipants = result.getInt("maxparticipants");
                    Course course = new Course(id, name, date, duration, price, category, teacher, experienceLevel, maxParticipants);
                    return Optional.of(course);
                }
            }
        } catch (Exception e) {
            System.out.println("Error DB " + e);
        }
        return Optional.empty();
    }

    @Override
    public Iterable<Course> findAll() {
        Connection conn = dbUtils.getConnection();
        List<Course> courses = new java.util.ArrayList<>();
        try(PreparedStatement preStmt = conn.prepareStatement("select * from course")) {
            try (ResultSet result = preStmt.executeQuery()) {
                while (result.next()) {
                    Integer id = result.getInt("id");
                    String name = result.getString("name");
                    LocalDateTime date = LocalDateTime.parse(result.getString("date"));
                    int duration = result.getInt("duration");
                    float price = result.getFloat("price");
                    CourseCategory category = CourseCategory.valueOf(result.getString("category"));
                    int id_t = result.getInt("idTeacher");
                    Optional<Teacher> teacherOpt = teacherRepo.findOne(id_t);
                    Teacher teacher = teacherOpt.orElse(null);
                    ExperienceLevel experienceLevel = ExperienceLevel.valueOf(result.getString("experiencelevel"));
                    int maxParticipants = result.getInt("maxparticipants");
                    Course course = new Course(id, name, date, duration, price, category, teacher, experienceLevel, maxParticipants);
                    courses.add(course);
                }
            }
        } catch (Exception e) {
            System.out.println("Error DB " + e);
        }
        return courses;
    }
}
