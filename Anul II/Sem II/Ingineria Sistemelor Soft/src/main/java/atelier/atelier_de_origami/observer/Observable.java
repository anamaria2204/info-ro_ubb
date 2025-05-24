package atelier.atelier_de_origami.observer;

import atelier.atelier_de_origami.events.Event;

public interface Observable<E extends Event> {
    void addObserver(Observer<E> e);
    void removeObserver(Observer<E> e);
    void notifyObservers(E t);
}