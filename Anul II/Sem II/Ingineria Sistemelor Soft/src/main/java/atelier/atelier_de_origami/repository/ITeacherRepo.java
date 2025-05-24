package atelier.atelier_de_origami.repository;

import atelier.atelier_de_origami.domain.Teacher;

public interface ITeacherRepo extends IRepository<Integer, Teacher> {
    void save(Teacher teacher);
    Teacher findByUsername(String username);
}
