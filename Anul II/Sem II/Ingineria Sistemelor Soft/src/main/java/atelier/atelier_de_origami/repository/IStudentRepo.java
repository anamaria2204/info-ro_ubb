package atelier.atelier_de_origami.repository;
import atelier.atelier_de_origami.domain.Student;

public interface IStudentRepo extends IRepository<Integer, Student> {
    void save(Student student);
    Student findByUsername(String username);
}
