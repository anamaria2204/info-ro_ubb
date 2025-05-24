package atelier.atelier_de_origami.repository.hibernate;

import atelier.atelier_de_origami.domain.Teacher;
import atelier.atelier_de_origami.repository.ITeacherRepo;
import atelier.atelier_de_origami.repository.database.EncryptUtils;
import org.hibernate.Session;
import org.hibernate.Transaction;
import org.hibernate.query.Query;

import java.util.List;
import java.util.Optional;

public class TeacherHibernateRepo implements ITeacherRepo {

    private static final EncryptUtils encryptUtils = new EncryptUtils();

    @Override
    public void save(Teacher teacher) {
        Transaction transaction = null;
        try (Session session = HibernateUtils.getSessionFactory().openSession()) {
            transaction = session.beginTransaction();
            teacher.setPassword(encryptUtils.encrypt1(teacher.getPassword()));
            session.persist(teacher);
            transaction.commit();
        } catch (Exception e) {
            if (transaction != null) {
                transaction.rollback();
            }
            throw new RuntimeException("Failed to save teacher", e);
        }
    }

    @Override
    public Teacher findByUsername(String username) {
        try (Session session = HibernateUtils.getSessionFactory().openSession()) {
            Query<Teacher> query = session.createQuery(
                "FROM Teacher WHERE username = :username", Teacher.class);
            query.setParameter("username", username);
            List<Teacher> teachers = query.getResultList();
            if (teachers.isEmpty()) {
                return null;
            }
            Teacher teacher = teachers.get(0);
            teacher.setPassword(encryptUtils.decrypt1(teacher.getPassword()));
            return teacher;
        } catch (Exception e) {
            throw new RuntimeException("Failed to find teacher by username", e);
        }
    }

    @Override
    public Optional<Teacher> findOne(Integer id) {
        try (Session session = HibernateUtils.getSessionFactory().openSession()) {
            Teacher teacher = session.find(Teacher.class, id);
            if (teacher != null) {
                teacher.setPassword(encryptUtils.decrypt1(teacher.getPassword()));
            }
            return Optional.ofNullable(teacher);
        } catch (Exception e) {
            throw new RuntimeException("Failed to find teacher by ID", e);
        }
    }

    @Override
    public Iterable<Teacher> findAll() {
        try (Session session = HibernateUtils.getSessionFactory().openSession()) {
            List<Teacher> teachers = session.createQuery(
                "FROM Teacher", Teacher.class).list();
            teachers.forEach(t ->
                t.setPassword(encryptUtils.decrypt1(t.getPassword())));
            return teachers;
        } catch (Exception e) {
            throw new RuntimeException("Failed to retrieve all teachers", e);
        }
    }
}