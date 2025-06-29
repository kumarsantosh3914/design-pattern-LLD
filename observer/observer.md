# Observer:
  - The observer pattern is a behavioral design pattern that establishes a one-two-many
    dependency (one subject and many obersers) between objects. In this pattern, when
    one object (the subject) changes its state, all its dependents (obersers) are notified
    and updated automatically.

# Components involved:
  1. Subject: It holds the state being observed. It maintains a list of obersers
     and provides methods for subscribing, unsubscribing, and notifiying obersers.

  2. Observer: This is the interface that defines the update method, which the
     subject calls to notify observed of any state changes.

  3. ConcreteSubject: This is a subclass of the subject class, which
     implements the specific behavior of subscribing, unsubscribing, and
     notifiying obersers. It also contains the actual state that obersers are
     interested in.

  4. ConcreteObserver: This is a subclass of the oberser interface that 
     implements the update method. Each concrete observer can define its
     behavior for handling updates from the subject.

![observer design diagram](https://miro.medium.com/v2/resize:fit:1100/format:webp/1*AlNMUufh-2JNHD4t4UkWMw.png)