import random # for testing


class Employee:
    #define the employee
    def __init__(self,E_name,E_age,E_salary) -> None:
          self.name = E_name
          self.age = E_age
          self.salary = E_salary
    #function to update the salary
    def update_salary(self,new_salary):
         self.salary = new_salary
    #function to get the age
    def return_age(self):
         return self.age


#store all the employess in a list
list_of_employes = {}

#function to add employees but doesnt remove duplicate names
def add_new_employee(E_name,E_age,E_salary):
     newEmployee = Employee(E_name,E_age,E_salary)
     list_of_employes[newEmployee.name] = newEmployee

#function to delete employes in an age range
def delete_employees(startAge, EndAge):
     deleted_keys = []
     for E_key in list_of_employes:
          if EndAge > list_of_employes[E_key].age and list_of_employes[E_key] > startAge:
               print(f"Deleteing --> {list_of_employes[E_key].name}")
               deleted_keys.append(E_key)
     print()
     for D_key in deleted_keys:
          list_of_employes.pop(D_key)



#Adds 10 employees with random ages and salary for debugging
for x in range(0,10):
     name = "Employe" + str(x)
     age = random.randint(20,64)
     salary = random.randint(1000,5433)
     add_new_employee(name, age , salary)


systemOFF = False

while not systemOFF:

    print("1)Add new employee\n" + 
          "2)Print all employees\n" + 
          "3)Delete by age\n" +
          "4)Update salary by name\n" +
          "5)End the program")
    
    #take the input
    keyword = input()

    if keyword == "1":
         print("Enter employee data")
         EName = input("Enter the name\n")
         try:
          EAge = int(input("Enter the age\n"))
         except:
              print("Age  must be a number")
              continue
         try:
               ESalary = int(input("Enter the salary\n"))
         except:
              print("Salary must be a number")
              continue
                   

         add_new_employee(EName,EAge,ESalary)
         print(f"\nEmployee:{EName} added!\n")


    elif keyword == "2":
         if len(list_of_employes) == 0:
              print("There are no employees\n")
              continue
         print("\t**Employees list**\t")
         for Employe_key in list_of_employes:
              curr = list_of_employes[Employe_key]
              print(f"Employee: {curr.name} has age {curr.age} and salary {curr.salary}")
         print()
         
    elif keyword == "3":
         try:
               startAge = int(input("Enter age from\n"))
               endAge = int(input("Enter age to\n"))
         except:
              print("Age must be a number.")
              continue

         delete_employees(startAge, endAge)



    elif keyword == "4":
         keyword = input("Enter the name of the employee\n")

         found = False

         for Employee_key in list_of_employes:
              if list_of_employes[Employee_key].name == keyword:
                   found = True
                   break


         if found:
              try:
                   new_salary = int(input("Enter new salary\n"))
              except:
                   print("salary must be a number")
              else:
                   list_of_employes[Employee_key].update_salary(new_salary)
                   print("Salary updated!")
         else:
              print("Employee not found.")
              
         




    elif keyword == "5":
         systemOFF = True
         print("User exited the program")
    else:
         print("Invaild. Try again.")
         
