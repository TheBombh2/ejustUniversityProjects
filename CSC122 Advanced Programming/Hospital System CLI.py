import random # used for inserting paitents with random status from 0 to 2
import os #just used for clearing the screen


class Patient:
    def __init__(self,P_spec = 0,P_status = -1,P_name = '') -> None:
        self.Specialization = P_spec     # There are 20 specs
        self.status = P_status    # 0(normal) < 1(urgent) < 2(super urgent) ----- -1(unassigned)
        self.name = P_name
       

class Specialization:
    def __init__(self,spec_ID):
        self.id = spec_ID
        self.Paitents = {}
        self.counter = 0
        self.max = 10
        self.duplicate_name_counter = 2

    #function to get the names in a spec. Useful for searching for a specific paitent by name to remove them from the list
    def get_paitents_names(self):
        final = []
        for paitent in self.Paitents.values():
            final.append(paitent.name)
        return final

        
#Dictionary to track all the available specs
current_avaliable_specs= {}

#adds a new paitent in a specific spec if that spec doesnt exist create a new one and insert the paitent in it
def add_new_patient(P_name,P_spec,P_status):
    if P_spec not in current_avaliable_specs:
        spec = Specialization(P_spec)
        current_avaliable_specs[P_spec] = spec

    current_spec = current_avaliable_specs[P_spec]
    
    if current_spec.counter < current_spec.max:

        new_patient = Patient(P_spec,P_status,P_name)
        current_spec.counter += 1 
        #in case of duplicate names
        if new_patient.name in current_spec.get_paitents_names():
            
            new_patient.name += str(current_spec.duplicate_name_counter)
            current_spec.duplicate_name_counter +=1

        current_spec.Paitents[new_patient.name] = new_patient
        #always sort the paitetns after every new paitent added
        #is not perfect since paitents in a specific status might change order
        sort_patients(current_spec.Paitents)
    else:
        print("Current Specialization is full and can't accept more patients")

    
def sort_patients(P_Dict):
    #as it name shows it sorts the paitents according to thier status 0(normal) < 1(urgent) < 2(super urgent)
    if len(P_Dict.keys()) == 1:
        return
    else:
        for p1_key in P_Dict:
            for p2_key in P_Dict:
                if P_Dict[p2_key].status < P_Dict[p1_key].status:
                    P_Dict[p1_key],P_Dict[p2_key] = P_Dict[p2_key],P_Dict[p1_key]
                else:
                    continue




    #adds 10 patients into spec 1 and 2 automaticaly
    #These are only for debugging
#for x in range (0,10):
 #   TP_name = 'TestPaitent' + str(x)
  #  TP_spec = 1
   # TP_status = random.randint(0,2)
    #add_new_patient(TP_name,TP_spec,TP_status)
    #add_new_patient(TP_name,TP_spec + 1,TP_status)

add_new_patient('belal',10,0)
add_new_patient('ahmed',10,0)
add_new_patient('mohamed',10,0)
add_new_patient('aly',10,0)


systemOff = False
while(not systemOff):


    
    print('\n1) Add new patient')
    print('2) Print all patients')
    print('3) Get next patient')
    print('4) Remove a leaving patient')
    print('5) End the program')
    keyword = input("Enter your choice (from 1 to 5) or (0) to clear the screen\n")
    
    #Add a new patient
    if keyword == '1':
        P_name = input("Enter name\n")
        
        if not P_name.isalpha():
            print("Paitent name musnt have a number")
            continue
            
            
        try:
            P_spec = int(input("Enter Specialization\n"))

        except:
            print("Specialization must be a number")
            continue

        #Spec must be between 1 and 20
        if P_spec <= 0 or P_spec > 20:
            print("\nThere are only 20 Specialization from (1 to 20)\n")
            continue
        try:
            P_status = int(input("Enter status (0 normal / 1 urgent / 2 super urgent)\n"))
        except:
            print("Paitent status must be 0,1 or 2")
            continue
        #There are only 3 status
        if P_status < 0 or P_status > 2:
            print("\nYou can only enter from the previous status\n")
            continue
        #call the function to add a new patient
        add_new_patient(P_name,P_spec,P_status)



    #print all patients in all specs
    elif keyword == '2':
        for spec_key in current_avaliable_specs:
            current_spec = current_avaliable_specs[spec_key]
            if len(current_spec.Paitents) == 0:
                continue
            print(f"\nThere are currently {len(current_spec.Paitents)} patients in Specialization {current_spec.id}")
            for patient_key in current_spec.Paitents.keys():
                patient = current_spec.Paitents[patient_key]
                status = 'super urgent' if patient.status == 2 else 'urgent' if patient.status == 1 else 'normal'  #Bro this is so cool
                print (f'Patient: {patient.name} is {status}')

    #Serve the paitent and remove from the queue
    elif keyword == '3':
        try:
            choosen_spec = int(input("Enter the specialization\n"))
        except:
            print("Specialization must be a number")
            continue
        try:
            currentt_spec = current_avaliable_specs[choosen_spec]
        except:
            print("Specilaiztion doesn't exist yet")
            continue
        if len(currentt_spec.Paitents) == 0:
                print("No other paitents in this Specialization. Take a rest Dr.")
                
        else:
            for paitent_key in currentt_spec.Paitents.keys():
                patient = currentt_spec.Paitents[paitent_key]
                print(f'{patient.name} please go with the Dr')
                del currentt_spec.Paitents[paitent_key]
                currentt_spec.counter -= 1
                break
        


    elif keyword == '4':
        try:
            choosen_spec = int(input("Enter the specialization:\n"))
        except:
            print("Specialization must be a number")
            
        patient_name = input("Enter the paitent name:\n")
        current_spec = current_avaliable_specs[choosen_spec]
        #searches for the name in the choosen spec
        if patient_name in current_spec.get_paitents_names():
            for paitent_key in current_spec.Paitents.keys():
                P_NAME = current_spec.Paitents[paitent_key].name
                if P_NAME == patient_name:
                    print(f"Paitent {P_NAME} was removed from the queue.")
                    del current_spec.Paitents[paitent_key]
                    current_spec.counter -=1
                    break
        else:
            print("No paitent with this name was found.")
            
    

    #clear the terminal
    elif keyword == '0':
        os.system('CLS')
    #exiting the program
    elif keyword == '5':
        systemOff = True        
    else:
        print("\nCouldn't understand input. Try again.")

#This print command is out of the while loop only happens of systemOff is True
print("User exited the program")