package atelier.atelier_de_origami.repository.database;

import atelier.atelier_de_origami.domain.Booking;
import atelier.atelier_de_origami.domain.Course;
import atelier.atelier_de_origami.domain.Student;
import atelier.atelier_de_origami.domain.Teacher;
import atelier.atelier_de_origami.repository.IBooking;
import atelier.atelier_de_origami.repository.ICourseRepo;
import atelier.atelier_de_origami.repository.IStudentRepo;
import atelier.atelier_de_origami.repository.ITeacherRepo;
import atelier.atelier_de_origami.utils.JdbcUtils;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.Timestamp;
import java.time.LocalDate;
import java.time.LocalDateTime;
import java.time.LocalTime;
import java.util.*;

public class BookingRepo implements IBooking {

    private JdbcUtils dbUtils;
    private final IBooking bookingRepo;
    private final ITeacherRepo teacherRepo;
    private final ICourseRepo courseRepo;
    private final IStudentRepo studentRepo;

    public BookingRepo(Properties props, IBooking bookingRepo, ITeacherRepo teacherRepo, IStudentRepo studentRepo, ICourseRepo courseRepo) {
        dbUtils = new JdbcUtils(props);
        this.bookingRepo = bookingRepo;
        this.studentRepo = studentRepo;
        this.teacherRepo = teacherRepo;
        this.courseRepo = courseRepo;
    }

    @Override
    public Booking save(Booking booking) {
        Connection conn = dbUtils.getConnection();
        try (PreparedStatement prepStmt = conn.prepareStatement(
                "insert into booking (id_student, id_teacher, id_course, course_time, booking_date) values (?, ?, ?, ?, ?)",
                PreparedStatement.RETURN_GENERATED_KEYS)) {

            prepStmt.setInt(1, booking.getStudent().getId());
            prepStmt.setInt(2, booking.getTeacher().getId());
            prepStmt.setInt(3, booking.getCourse().getId());
            prepStmt.setTimestamp(4, java.sql.Timestamp.valueOf(booking.getCourseTime()));
            prepStmt.setTimestamp(5, java.sql.Timestamp.valueOf(booking.getDate()));

            prepStmt.executeUpdate();
            return booking;

        } catch (Exception e) {
            System.out.println("Error DB " + e);
            return null;
        }
    }


    @Override
    public Booking delete(int id) {
        Optional<Booking> bookingOpt = findOne(id);
        Booking booking = bookingOpt.orElse(null);
        if (booking == null)
            return null;

        Connection conn = dbUtils.getConnection();
        try (PreparedStatement prepStmt = conn.prepareStatement(
                "delete from booking where id = ?")) {
            prepStmt.setInt(1, id);
            prepStmt.executeUpdate();
            return booking;

        } catch (Exception e) {
            System.out.println("Error DB " + e);
            return null;
        }
    }

    @Override
    public Booking update(Booking booking) {
        Connection conn = dbUtils.getConnection();
        try (PreparedStatement stmt = conn.prepareStatement(
                "UPDATE booking SET id_student = ?, id_teacher = ?, id_course = ?, booking_time = ?, course_date = ? WHERE id = ?")) {

            stmt.setInt(1, booking.getStudent().getId());
            stmt.setInt(2, booking.getTeacher().getId());
            stmt.setInt(3, booking.getCourse().getId());
            stmt.setTimestamp(4, Timestamp.valueOf(booking.getCourseTime()));
            stmt.setTimestamp(5, Timestamp.valueOf(booking.getDate()));
            stmt.setInt(6, booking.getId());

            int rowsUpdated = stmt.executeUpdate();
            return rowsUpdated > 0 ? booking : null;

        } catch (Exception e) {
            System.out.println("Error DB (update): " + e);
            return null;
        }
    }


    @Override
    public Iterable<Booking> findAllBookingsStudent(int idStudent) {
        return findAllBy("id_student", idStudent);
    }

    @Override
    public Iterable<Booking> findAllBookingsTeacher(int idTeacher) {
        return findAllBy("id_teacher", idTeacher);
    }

    @Override
    public Iterable<Booking> findAllBookingsCourse(int idCourse) {
        return findAllBy("id_course", idCourse);
    }

    @Override
    public List<Student> findAllStudentsByCourseAndTeacher(int courseId, int teacherId) {
        return List.of();
    }

    @Override
    public Optional findOne(Integer integer) {
        return Optional.empty();
    }

    @Override
    public Iterable<Booking> findAll() {
        List<Booking> bookings = new ArrayList<>();
        Connection conn = dbUtils.getConnection();
        try (PreparedStatement stmt = conn.prepareStatement("SELECT * FROM booking")) {
            var rs = stmt.executeQuery();
            while (rs.next()) {
                int id = rs.getInt("id");
                int idStudent = rs.getInt("id_student");
                int idTeacher = rs.getInt("id_teacher");
                int idCourse = rs.getInt("id_course");

                java.sql.Timestamp courseDateStamp = rs.getTimestamp("course_date");
                java.sql.Timestamp bookingTimeStamp = rs.getTimestamp("booking_time");

                LocalDateTime courseTime = bookingTimeStamp.toLocalDateTime();
                LocalDateTime courseDate = courseDateStamp.toLocalDateTime();

                Optional<Student> studentOpt = studentRepo.findOne(idStudent);
                Student student = studentOpt.orElse(null);
                Optional<Teacher> teacherOpt = teacherRepo.findOne(idTeacher);
                Teacher teacher = teacherOpt.orElse(null);
                Optional<Course> courseOpt = courseRepo.findOne(idCourse);
                Course course = courseOpt.orElse(null);

                Booking booking = new Booking(
                        id,
                        student,
                        teacher,
                        course,
                        courseDate,
                        courseTime
                );
                bookings.add(booking);
            }

        } catch (Exception e) {
            System.out.println("Error DB " + e);
        }

        return bookings;
    }

    private Iterable<Booking> findAllBy(String column, int id) {
        List<Booking> bookings = new ArrayList<>();
        Connection conn = dbUtils.getConnection();
        String query = "SELECT * FROM booking WHERE " + column + " = ?";
        try (PreparedStatement stmt = conn.prepareStatement(query)) {
            stmt.setInt(1, id);
            ResultSet rs = stmt.executeQuery();
            while (rs.next()) {
                Booking booking = extractBookingFromResultSet(rs);
                bookings.add(booking);
            }

        } catch (Exception e) {
            System.out.println("Error DB (findAllBy " + column + "): " + e);
        }

        return bookings;
    }

    private Booking extractBookingFromResultSet(ResultSet rs) throws Exception {
        int id = rs.getInt("id");
        int idStudent = rs.getInt("id_student");
        int idTeacher = rs.getInt("id_teacher");
        int idCourse = rs.getInt("id_course");

        LocalDateTime bookingTime = rs.getTimestamp("booking_time").toLocalDateTime();
        LocalDateTime courseDate = rs.getTimestamp("course_date").toLocalDateTime();

        Optional<Student> studentOpt = studentRepo.findOne(idStudent);
        Student student = studentOpt.orElse(null);
        Optional<Teacher> teacherOpt = teacherRepo.findOne(idTeacher);
        Teacher teacher = teacherOpt.orElse(null);
        Optional<Course> courseOpt = courseRepo.findOne(idCourse);
        Course course = courseOpt.orElse(null);


        return new Booking(id, student, teacher, course, bookingTime, courseDate);
    }


}
