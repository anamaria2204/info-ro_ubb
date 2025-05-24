package atelier.atelier_de_origami.repository.hibernate;

import atelier.atelier_de_origami.domain.Student;
import atelier.atelier_de_origami.repository.IStudentRepo;
import atelier.atelier_de_origami.repository.database.EncryptUtils;
import org.hibernate.Session;
import org.hibernate.Transaction;
import org.hibernate.query.Query;

import java.util.List;
import java.util.Optional;

public class StundetHibernateRepo implements IStudentRepo {

    private static final EncryptUtils encryptUtils = new EncryptUtils();

    @Override
    public void save(Student student) {
        Transaction transaction = null;
        try(Session session = HibernateUtils.getSessionFactory().openSession()){
            transaction = session.beginTransaction();
            String encryptedPassword = encryptUtils.encrypt1(student.getPassword());
            student.setPassword(encryptedPassword);
            session.persist(student);
            transaction.commit();
        }
        catch(Exception e){
            if(transaction != null) {
                transaction.rollback();
            }
            throw  new RuntimeException("Failed to save student", e);
        }
    }

    @Override
    public Student findByUsername(String username) {
        try (Session session = HibernateUtils.getSessionFactory().openSession()) {
            Query<Student> query = session.createQuery(
                "FROM Student WHERE username = :username", Student.class);
            query.setParameter("username", username);
            List<Student> students = query.getResultList();
            if (students.isEmpty()) {
                return null;
            }
            Student student = students.get(0);
            student.setPassword(encryptUtils.decrypt1(student.getPassword()));
            return student;
        } catch (Exception e) {
            throw new RuntimeException("Failed to find student by username", e);
        }
    }

    @Override
    public Optional findOne(Integer id) {
        try (Session session = HibernateUtils.getSessionFactory().openSession()) {
            Student student = session.find(Student.class, id);
            if (student != null) {
                student.setPassword(encryptUtils.decrypt1(student.getPassword()));
            }
            return Optional.ofNullable(student);
        } catch (Exception e) {
            throw new RuntimeException("Failed to find student by ID", e);
        }
    }

    @Override
    public Iterable<Student> findAll() {
        try (Session session = HibernateUtils.getSessionFactory().openSession()) {
            List<Student> students = session.createQuery(
                "FROM Student", Student.class).list();
            students.forEach(s ->
                s.setPassword(encryptUtils.decrypt1(s.getPassword())));
            return students;
        } catch (Exception e) {
            throw new RuntimeException("Failed to retrieve all students", e);
        }
    }
}
