/*
 * assignment2.cpp
 *
 *  Created on: May 23, 2018
 *      Author: Jiazhen Tang
 */


#include "Department.h"
#include "Course.h"
#include "Section.h"
#include "Person.h"


namespace CS_5004 {

class Department;
class Section;
class Person;
class Course;

/**
 * Create a new department.
 *
 * @param name department name
 * @param maxCourses the maximum number of courses
 * @param maxMembers the maximum number of members
 */
Department::Department(const string &name, unsigned int maxCourses,
        unsigned int maxMembers) {
    this->deptName = name;
    this->maxCourses = maxCourses;
    this->maxMembers = maxMembers;
    this->theCourses = new Course*[maxCourses]();
    this->theMembers = new Person*[maxMembers]();
}

/**
 * Department destructor.
 */
Department::~Department() {
    for (int i = 0; i < maxCourses; i++) {
        delete theCourses[i];
        theCourses[i] = nullptr;
    }
    for (int i = 0; i < maxMembers; i++) {
        delete theMembers[i];
        theMembers[i] = nullptr;
    }
    delete [] theCourses;
    theCourses = nullptr;
    delete [] theMembers;
    theMembers = nullptr;
    maxCourses = 0;
    maxMembers = 0;
}

/**
 * Returns the name of the department.
 *
 * @return the name of the department
 */
const string &Department::name() const{
    return this->deptName;
}

/**
 * Add new student or teacher to the department
 *
 * @param givenName the person's first name
 * @param familyName the person's family name
 * @return the new student or teacher, or nullptr if could not add
 */
Person* Department::addMember(const string &familyName, const string &givenName) {
    Person* person = new Person(familyName, givenName, this);
    if (theMembers[maxMembers - 1] != NULL) {
        return NULL;
    }
    for (int i = 0; i < maxMembers; i++) {
        if (theMembers[i] == NULL) {
            theMembers[i] = person;
            break;
        }
    }
    return person;
}

/**
 * Finds the person by their family and given names
 *
 * @param familyName the family name
 * @param givenName the given name
 * @return the person or nullptr of person not found
 */
Person* Department::findMember(const string &familyName, const string &givenName) const {
    Person * p = NULL;
    for (int i = 0; i < maxMembers; i++) {
        if (theMembers[i]->familyName() == familyName && theMembers[i]->givenName() == givenName) {
            p = theMembers[i];
            break;
        }
    }
    return p;
}

/**
 * Fill in the array of members of this department, up to maxMembers.
 *
 * @param members the array of members or nullptr for count only
 * @param nMembers the maximum number of members to return
 * @return the actual number of members returned
 */
unsigned int Department::members(Person *members[], int nMembers) const {
    int max = 0;
    if (nMembers < maxMembers) {
        max = nMembers;
    } else {
        max = maxMembers;
    }
    int count = 0;
    for (int i = 0; i < nMembers; i++) {
        if (theMembers[i] != NULL) {
            members[i] = theMembers[i];
            count++;
        }
    }
    return count;
}


/**
 * Returns number of members currently in the department.
 *
 * @return number of members currently in the department
 */
unsigned int Department::numMembers() const {
    int number = 0;
    for (int i = 0; i < maxMembers; i++) {
        if (theMembers[i] != NULL) {
            number++;
        } else {
            break;
        }
    }
    return number;
}

/**
 * Add a course for the department.
 *
 * @param courseName the name of the course
 * @param maxSections the maximum number of sections available
 * @return the new course or nullptr if the course could not be added
 */
Course* Department::addCourse(const string &courseName, unsigned int nSections) {
    Course * course = new Course(courseName, nSections,this);
    if (theCourses[maxCourses - 1] != NULL) {
            return NULL;
    }
    for (int i = 0; i < maxCourses; i++) {
        if (theCourses[i] == NULL) {
            theCourses[i] = course;
            break;
        }
    }
    return course;
}

/**
 * Finds the course by its course name.
 *
 * @param courseName the course name
 * @return the course or nullptr if course not found
 */
Course* Department::findCourse(const string &courseName) const {
    Course * c = NULL;
    for (int i = 0; i < maxCourses; i++) {
        if (theCourses[i]->name() == courseName) {
            c = theCourses[i];
            break;
        }
    }
    return c;
}

/**
 * Fill in the array of courses of this department, up to maxCourses.
 *
 * @param courses the array of courses or nullptr for count only
 * @param nCourses the maximum number of courses to return
 * @return the actual number of courses returned
 */
unsigned int Department:: courses(Course *courses[], int nCourses) const {
    int max = 0;
    if (nCourses < maxCourses) {
        max = nCourses;
    } else {
        max = maxCourses;
    }
    int count = 0;
    for (int i = 0; i < nCourses; i++) {
        if (theCourses[i] != NULL) {
            courses[i] = theCourses[i];
            count++;
        }
    }
    return count;
}

/**
 * Returns number of courses currently offered by the department.
 *
 * @return number of courses currently offered by the department
 */
unsigned int Department::numCourses() const {
    int number = 0;
    for (int i = 0; i < maxCourses; i++) {
        if (theCourses[i] != NULL) {
            number++;
        } else {
            break;
        }
    }
    return number;
}


/**
 * Creates a new student or teacher.
 *
 * @param familyName the family name
 * @param givenName the given name
 * @param dept the department
 */
Person::Person(const string &familyName, const string &givenName, Department *dept) {
    this->theFamilyName = familyName;
    this->theGivenName = givenName;
    this->theDept = dept;
}

/**
 * Person destructor
 */
Person::~Person() {
    theDept = nullptr;
}

/**
 * Return the student or teacher given name.
 *
 * @return the student or teacher given name.
 */
const string & Person::givenName() const {
    return this->theGivenName;
}

/**
 * Return the student or teacher family name.
 *
 * @return the student or teacher family name
 */
const string & Person::familyName() const {
    return this->theFamilyName;
}

/**
 * Return the department of this student or teacher.
 *
 * @return the student or teacher department
 */
Department* Person::department() const {
    return this->theDept;
}

/**
 * Add this student to a section of a course.
 *
 * @param course the course
 * @param sectionNum the section number
 * @return true if the course was added
 */
bool Person::addCourse(Course* course, unsigned int sectionNum) {
    Section* section = course->findSection(sectionNum);
    return section->addStudent(this);
}

/**
 * Create a new course.
 * @param courseName the course name
 * @param maxSections max number of sections
 * @param dept the department
 */
Course::Course(const string &courseName, unsigned int maxSections, Department *dept) {
    this->courseName = courseName;
    this->maxSections = maxSections;
    this->theDept = dept;
    this->theSections = new Section*[maxSections]();
}

/**
 * Course destructor
 */
Course::~Course() {
    for (int i = 0; i < maxSections; i++) {
        delete theSections[i];
        theSections[i] = nullptr;
    }
    delete[] theSections;
    theSections = nullptr;
    maxSections = 0;
}

/**
 * Returns course name
 *
 * @return name of course
 */
const string &Course::name() const {
    return this->courseName;
}

/**
 * Gets department for this course.
 *
 * @return the department
 */
Department * Course::department() const {
    return this->theDept;
}

/**
 * Add a section for this course.
 *
 * @Prime teacher the teacher
 * @param capacity the course capacity
 * @return the new section
 */
Section* Course::addSection(Person* teacher, unsigned int capacity) {
    if (theSections[maxSections - 1] != NULL) {
        return NULL;
    }
    int sectionnum = this->numSections() + 1;
    Section * section = new Section(teacher, this, sectionnum, capacity);
    theSections[sectionnum - 1] = section;
    return section;
}

/**
 * Find section by number.
 *
 * @param sectionNum the section number
 * @return the section ny number
 */
Section * Course::findSection(unsigned int sectionNum) const {
    Section * s = NULL;
    for (int i = 0; i < maxSections; i++) {
        if (theSections[i]->sectionNumber() == sectionNum) {
            s = theSections[i];
            break;
        }
    }
    return s;
}

/**
 * Fill in the array of sections for this course, up to nSections.
 *
 * @param sections the array of sections
 * @param nSections the maximum number of sections to return
 * @return the actual number of sections returned
 */
unsigned int Course::sections(Section *sections[], int nSections) const {
    int max = 0;
    if (nSections < maxSections) {
        max = nSections;
    } else {
        max = maxSections;
    }
    int count = 0;
    for (int i = 0; i < nSections; i++) {
        if (theSections[i] != NULL) {
            sections[i] = theSections[i];
            count++;
        }
    }
    return count;
}

/**
 * Returns number of sections currently offered.
 *
 * @return number of sections currently offered
 */
unsigned int Course::numSections() const {
    int number = 0;
    for (int i = 0; i < maxSections; i++) {
        if (theSections[i] != NULL) {
            number++;
        } else {
            break;
        }
    }
    return number;
}

/**
 * Returns course enrollment
 *
 * @return enrollment for all sections
 */
unsigned int Course::enrollment() const {
    int number = 0;
    for (int i = 0; i < maxSections; i++) {
        number = number + theSections[i]->enrollment();
    }
    return number;
}

/**
 * Create a section of a course with a given capacity.
 *
 * @param teacher the teacher for the section
 * @param course the course
 * @param sectionNum the section number
 * @param capacity the section capacity
 */
Section::Section(Person *teacher, Course *course, unsigned int sectionNum, unsigned int capacity) {
    this->theTeacher = teacher;
    this->theCourse = course;
    this->theSectionNum = sectionNum;
    this->theCapacity = capacity;
    this->theStudents = new Person*[capacity]();
}

/**
 * Section destructor.
 */
Section::~Section() {
    for (int i = 0; i < theCapacity; i++) {
        theStudents[i] = nullptr;
    }
    delete [] theStudents;
    theStudents = nullptr;
    theTeacher = nullptr;
    theCourse = nullptr;
    theCapacity = 0;
    theSectionNum = 0;
}

/**
 * Returns the section number.
 *
 * @return the section number for this section.
 */
unsigned int Section::sectionNumber() const {
    return this->theSectionNum;
}

/**
 * Returns the course for this section.
 *
 * @return the course for this section.
 */
Course * Section::course() const {
    return this->theCourse;
}

/**
 * The teacher for this section.
 *
 * @return the teacher for this section
 */
Person * Section::teacher() const {
    return this->theTeacher;
}

/**
 * Add a student to this section.
 *
 * @param student the student
 * @return true if the student was added, or false
 * if person is the teacher, the person was already
 * in the section, or the section is at capacity
 */
bool Section::addStudent(Person *student) {
    if (student->givenName() == this->teacher()->givenName()
            && student->familyName() == this->teacher()->familyName()) {
        return false;
    }
    if (theStudents[theCapacity - 1] != NULL) {
        return false;
    }
    for (int i = 0; i < theCapacity; i++) {
        if (theStudents[i] == NULL) {
            theStudents[i] = student;
            break;
        }
        if (student->givenName() == theStudents[i]->givenName()
                && student->familyName() == theStudents[i]->familyName()) {
            return false;
        }
    }
    return true;
}


/**
 * Fill in the array of students for this section, up to maxStudents.
 *
 * @param students the array of students
 * @param maxStudents the maximum number of students to return
 * @return the actual number of students returned
 */
unsigned int Section::students(Person *students[], int maxStudents) const {
    int max = 0;
    if (maxStudents < theCapacity) {
        max = maxStudents;
    } else {
        max = theCapacity;
    }
    int count = 0;
    for (int i = 0; i < maxStudents; i++) {
        if (theStudents[i] != NULL) {
            students[i] = theStudents[i];
            count++;
        }
    }
    return count;
}

/**
 * The number of students enrolled in this section.
 *
 * @return the number of students enrolled in this section
 */
unsigned int Section::enrollment() const {
    int number = 0;
    for (int i = 0; i < theCapacity; i++) {
        if (theStudents[i] != NULL) {
            number++;
        } else {
            break;
        }
    }
    return number;
}

/**
 * Returns the section capacity.
 *
 * @return the section capacity
 */
unsigned int Section::capacity() const {
    return this->theCapacity;
}

} /* namespace CS_5004 */
