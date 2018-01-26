package com.team254.lib;

import java.util.Hashtable;

/**
 * Singleton which keeps a running list of all subsystems.
 * @author spinkerton
 */
public class SubsystemLister {

  private static SubsystemLister instance = null;

  public static SubsystemLister getSubsystemLister() {
    if (instance == null) {
      instance = new SubsystemLister();
    }
    return instance;
  }
  private Hashtable systems = new Hashtable();

  private SubsystemLister() {
  }

  public void addSubsystem(String name, Subsystem s) {
    System.out.println("adding: " + name);
    systems.put(name, s);
  }

  public Subsystem get(String name) {
    Subsystem s = (Subsystem) systems.get(name);
    return s;
  }

  public String toString() {
    return systems.toString();
  }
}
