//
//  ContentView.swift
//  Swift_RegistrationForm
//
//  Created by 張芯翎 on 2023/10/22.
//

import SwiftUI
import SwiftData

struct ContentView: View {
    @State private var showModal = false
    @FocusState var focus:FocusedField?
    @State var personProfile = Profile()
    @State var isValid = Valid()
    @State var test = true
    var genders = ["Female", "Male"]
    
    init() {
        //Use this if NavigationBarTitle is with Large Font
        //Use this if NavigationBarTitle is with displayMode = .inline
        UINavigationBar.appearance().titleTextAttributes = [.font : UIFont(name: "Georgia-Bold", size: 25)!]
    }

    enum FocusedField: Hashable{
        case first, initials, middle, last, street_addr, street_addr2, city, region, postal, home_tel, mobile_tel, email
    }
    
    var body: some View {
        NavigationView {
            VStack {
                Form {
                    NameSectionView(personProfile: $personProfile, isValid: $isValid)
                    
                    Section(header: Text("Gender")) {
                        Picker(selection: $personProfile.genderIndex, label: Text("Gender")) {
                            ForEach(genders.indices, id: \.self) {
                                index in Text(genders[index])
                            }
                        }
                        .pickerStyle(.menu)
                    }
                    
                    Section(header: Text("Birthday")) {
                        DatePicker("Birthday", selection: $personProfile.birthday, in: ...Date(), displayedComponents: .date)
                    }
                    
                    PreferredSectionView(personProfile: $personProfile, isValid: $isValid)
                    
                    AddressSectionView(personProfile: $personProfile, isValid: $isValid)
                                        
                    Section(header: Text("Home Telephone Number")){
                        TextField("### ### ####", text: $personProfile.home_tel)
                            .focused($focus, equals: .home_tel)
                            .onAppear{
                                UITextField.appearance().clearButtonMode = .whileEditing
                            }
                            .submitLabel(.done)
                            .onSubmit {
                                focus = .mobile_tel
                            }
                            .onChange(of: personProfile.home_tel) {
                                isValid.home_tel = personProfile.home_tel.isEmpty
                            }
                            .overlay(RoundedRectangle(cornerRadius: 5).stroke(isValid.home_tel ? Color.red : Color.gray).frame(width:350, height: 40))
                    }
                    
                    Section(header: Text("Mobile Telephone Number")){
                        TextField("### ### ####", text: $personProfile.mobile_tel)
                            .focused($focus, equals: .mobile_tel)
                            .onAppear{
                                UITextField.appearance().clearButtonMode = .whileEditing
                            }
                            .submitLabel(.done)
                            .onSubmit {
                                focus = .email
                            }
                            .onChange(of: personProfile.mobile_tel) {
                                isValid.mobile_tel = personProfile.mobile_tel.isEmpty
                            }
                            .overlay(RoundedRectangle(cornerRadius: 5).stroke(isValid.mobile_tel ? Color.red : Color.gray).frame(width:350, height: 40))
                    }
                    
                    Section(header: Text("Email")){
                        TextField("Email", text: $personProfile.email)
                            .focused($focus, equals: .email)
                            .onAppear{
                                UITextField.appearance().clearButtonMode = .whileEditing
                            }
                            .submitLabel(.done)
                            .textFieldStyle(PlainTextFieldStyle())
                            .onChange(of: personProfile.email) {
                                isValid.email = personProfile.email.isEmpty
                            }
                            .overlay(RoundedRectangle(cornerRadius: 5).stroke(isValid.email ? Color.red : Color.gray).frame(width:350, height: 40))

                    }
                    
                    Section {
                        Button(action: {
                            if((personProfile.first.isEmpty || personProfile.last.isEmpty || personProfile.contact_addr.isEmpty || personProfile.street_addr.isEmpty || personProfile.city.isEmpty || personProfile.region.isEmpty || personProfile.postal.isEmpty || personProfile.home_tel.isEmpty || personProfile.mobile_tel.isEmpty || personProfile.email.isEmpty)){
                                showModal = false
                            }
                            else{
                                showModal = true
                            }
                        }) {
                            Text("Send")
                                .frame(minWidth: 0, maxWidth: .infinity)
                                .padding()
                                .foregroundColor(.white)
                                .background((personProfile.first.isEmpty || personProfile.last.isEmpty || personProfile.contact_addr.isEmpty || personProfile.street_addr.isEmpty || personProfile.city.isEmpty || personProfile.region.isEmpty || personProfile.postal.isEmpty || personProfile.home_tel.isEmpty || personProfile.mobile_tel.isEmpty || personProfile.email.isEmpty) ? Color.gray : Color.blue)
                                .cornerRadius(10)
                                .disabled((personProfile.first.isEmpty || personProfile.last.isEmpty || personProfile.contact_addr.isEmpty || personProfile.street_addr.isEmpty || personProfile.city.isEmpty || personProfile.region.isEmpty || personProfile.postal.isEmpty || personProfile.home_tel.isEmpty || personProfile.mobile_tel.isEmpty || personProfile.email.isEmpty))
                        }
                    }
                }
            }
            .navigationBarTitle("Personal Information Form", displayMode: .inline)
            .sheet(isPresented: $showModal, content: {
                ModalView(profile: personProfile)
            })
        }
    }
}

struct ModalView: View {
    var profile: Profile
    var title = ""
    
    var body: some View {
        NavigationView {
            List {
                Section(header: Text("Name").bold()){
                    if(profile.titleIndex == 0){
                        Text("Title: Ms")
                    }
                    else if(profile.titleIndex == 1){
                        Text("Title: Miss")
                    }
                    else if(profile.titleIndex == 2){
                        Text("Title: Mrs")
                    }
                    else if(profile.titleIndex == 3){
                        Text("Title: Mr")
                    }
                    Text("First: \(profile.first)")
                    if(profile.initials.isEmpty == false){
                        Text("Initials: \(profile.initials)")
                    }
                    if(profile.middle.isEmpty == false){
                        Text("Middle: \(profile.middle)")
                    }
                    Text("Last: \(profile.last)")
                }
                
                Section(header: Text("Gender").bold()){
                    if(profile.genderIndex == 0){
                        Text("Female")
                    }
                    else{
                        Text("Male")
                    }
                }
                
                Section(header: Text("Birthday").bold()){
                    Text("\(profile.birthday.formatted(date: .long, time: .omitted))")
                }
                
                Section(header: Text("Preferred Contact Address").bold()){
                    Text("\(profile.contact_addr)")
                }
                
                Section(header: Text("Address").bold()){
                    Text("Street address: \(profile.street_addr)")
                    if(profile.street_addr2.isEmpty == false){
                        Text("\(profile.street_addr2)")
                    }
                    Text("City: \(profile.city)")
                    Text("Region: \(profile.region)")
                    Text("Postal/Zip Code: \(profile.postal)")
                    Text("Country: \(Locale.current.localizedString(forRegionCode: profile.country) ?? "")")
                }
                
                Section(header: Text("Home Telephone Number").bold()){
                    Text("\(profile.home_tel)")
                }
                
                Section(header: Text("Mobile Telephone Number").bold()){
                    Text("\(profile.mobile_tel)")
                }
                
                Section(header: Text("Email").bold()){
                    Text("\(profile.email)")
                }
            }
            .listStyle(GroupedListStyle())
            .font(.system(size: 20))
            .navigationBarTitle("Registered Information")
        }
    }
}

struct NameSectionView: View {
    @Binding var personProfile: Profile
    @Binding var isValid: Valid
    var titles = ["Ms", "Miss", "Mrs", "Mr"]
    @FocusState private var focus: ContentView.FocusedField?

    var body: some View {
        Section(header: Text("Name")) {
            HStack{
                Picker(selection: $personProfile.titleIndex, label: Text("Title")) {
                    ForEach(titles.indices, id: \.self) { // id 將決定 Text 對應的 tag
                        index in Text(titles[index])
                    }
                }
                .pickerStyle(.menu)
                .frame(width: 105)
                .clipped()
                TextField("First", text: $personProfile.first)
                    .frame(width: 130)
                    .textFieldStyle(RoundedBorderTextFieldStyle())
                    .fixedSize(horizontal: true, vertical: false)
                    .focused($focus, equals: .first)
                    .onAppear{
                        UITextField.appearance().clearButtonMode = .whileEditing
                    }
                    .submitLabel(.done)
                    .onSubmit {
                        focus = .initials
                    }
                    .onChange(of: personProfile.first) {
                        isValid.first = personProfile.first.isEmpty
                    }
                    .overlay(RoundedRectangle(cornerRadius: 5).stroke(isValid.first ? Color.red : Color.gray).frame(width:130, height: 32))
                TextField("Initials", text: $personProfile.initials)
                    .frame(width: 70)
                    .textFieldStyle(RoundedBorderTextFieldStyle())
                    .fixedSize(horizontal: true, vertical: false)
                    .focused($focus, equals: .initials)
                    .onAppear{
                        UITextField.appearance().clearButtonMode = .whileEditing
                    }
                    .submitLabel(.done)
                    .onSubmit {
                        focus = .middle
                    }
                    .overlay(RoundedRectangle(cornerRadius: 5).stroke(Color.gray).frame(width:70, height: 32))
            }
            HStack{
                TextField("Middle", text: $personProfile.middle)
                    .frame(width: 150)
                    .textFieldStyle(RoundedBorderTextFieldStyle())
                    .fixedSize(horizontal: true, vertical: false)
                    .focused($focus, equals: .middle)
                    .onAppear{
                        UITextField.appearance().clearButtonMode = .whileEditing
                    }
                    .submitLabel(.done)
                    .onSubmit {
                        focus = .last
                    }
                    .overlay(RoundedRectangle(cornerRadius: 5).stroke(Color.gray).frame(width:150, height: 32))
                TextField("Last", text: $personProfile.last)
                    .frame(width: 160)
                    .textFieldStyle(RoundedBorderTextFieldStyle())
                    .fixedSize(horizontal: true, vertical: false)
                    .focused($focus, equals: .last)
                    .onAppear{
                        UITextField.appearance().clearButtonMode = .whileEditing
                    }
                    .submitLabel(.done)
                    .onChange(of: personProfile.last) {
                        isValid.last = personProfile.last.isEmpty
                    }
                    .overlay(RoundedRectangle(cornerRadius: 5).stroke(isValid.last ? Color.red : Color.gray).frame(width:160, height: 32))
            }
        }
    }
}

struct PreferredSectionView: View {
    @Binding var personProfile: Profile
    @Binding var isValid: Valid
    @FocusState private var focus: ContentView.FocusedField?
    
    @State var flagHome = false
    @State var flagWork = false
    @State var flagOther = false
    
    var body: some View {
        Section(header: Text("Preferred Contact Address")){
            HStack{
                Image(systemName: flagHome ? "checkmark.circle.fill": "circle")
                Text("Home")
            }.onTapGesture {
                flagHome = true
                flagWork = false
                flagOther = false
                personProfile.contact_addr = "Home"
            }
            HStack{
                Image(systemName: flagWork ? "checkmark.circle.fill": "circle")
                Text("Work")
            }.onTapGesture {
                flagHome = false
                flagWork = true
                flagOther = false
                personProfile.contact_addr = "Work"
            }
            HStack{
                Image(systemName: flagOther ? "checkmark.circle.fill": "circle")
                Text("Other")
            }.onTapGesture {
                flagHome = false
                flagWork = false
                flagOther = true
                personProfile.contact_addr = ""
            }
            if(flagOther){
                TextField("Other", text: $personProfile.contact_addr)
            }
        }
    }
}

struct AddressSectionView: View {
    @Binding var personProfile: Profile
    @Binding var isValid: Valid
    @FocusState private var focus: ContentView.FocusedField?
    
    var body: some View {
        Section(header: Text("Address")){
            TextField("Street Address", text: $personProfile.street_addr)
                .frame(width: 340)
                .textFieldStyle(RoundedBorderTextFieldStyle())
                .focused($focus, equals: .street_addr)
                .onAppear{
                    UITextField.appearance().clearButtonMode = .whileEditing
                }
                .submitLabel(.done)
                .onSubmit {
                    focus = .street_addr2
                }
                .onChange(of: personProfile.street_addr) {
                    isValid.street_addr = personProfile.street_addr.isEmpty
                }
                .overlay(RoundedRectangle(cornerRadius: 5).stroke(isValid.street_addr ? Color.red : Color.gray).frame(width:340, height: 35))
            TextField("Street Address Line 2", text: $personProfile.street_addr2)
                .frame(width: 340)
                .textFieldStyle(RoundedBorderTextFieldStyle())
                .focused($focus, equals: .street_addr2)
                .onAppear{
                    UITextField.appearance().clearButtonMode = .whileEditing
                }
                .submitLabel(.done)
                .onSubmit {
                    focus = .city
                }
                .overlay(RoundedRectangle(cornerRadius: 5).stroke(Color.gray).frame(width:340, height: 35))
            HStack{
                TextField("City", text: $personProfile.city)
                    .frame(width: 150)
                    .textFieldStyle(RoundedBorderTextFieldStyle())
                    .fixedSize(horizontal: true, vertical: false)
                    .focused($focus, equals: .city)
                    .onAppear{
                        UITextField.appearance().clearButtonMode = .whileEditing
                    }
                    .submitLabel(.done)
                    .onSubmit {
                        focus = .region
                    }
                    .onChange(of: personProfile.city) {
                        isValid.city = personProfile.city.isEmpty
                    }
                    .overlay(RoundedRectangle(cornerRadius: 5).stroke(isValid.city ? Color.red : Color.gray).frame(width:150, height: 35))
                TextField("Region", text: $personProfile.region)
                    .frame(width: 160)
                    .textFieldStyle(RoundedBorderTextFieldStyle())
                    .fixedSize(horizontal: true, vertical: false)
                    .focused($focus, equals: .region)
                    .onAppear{
                        UITextField.appearance().clearButtonMode = .whileEditing
                    }
                    .submitLabel(.done)
                    .onSubmit {
                        focus = .postal
                    }
                    .onChange(of: personProfile.region) {
                        isValid.region = personProfile.region.isEmpty
                    }
                    .overlay(RoundedRectangle(cornerRadius: 5).stroke(isValid.region ? Color.red : Color.gray).frame(width:160, height: 35))
            }
            TextField("Postal / Zip Code", text: $personProfile.postal)
                .frame(width: 150)
                .textFieldStyle(RoundedBorderTextFieldStyle())
                .fixedSize(horizontal: true, vertical: false)
                .focused($focus, equals: .region)
                .onAppear{
                    UITextField.appearance().clearButtonMode = .whileEditing
                }
                .submitLabel(.done)
                .onChange(of: personProfile.postal) {
                    isValid.postal = personProfile.postal.isEmpty
                }
                .overlay(RoundedRectangle(cornerRadius: 5).stroke(isValid.postal ? Color.red : Color.gray).frame(width:150, height: 35))
            Picker(selection: $personProfile.country, label: Text("Country")) {
                ForEach(NSLocale.isoCountryCodes, id: \.self) {
                    countryCode in Text(Locale.current.localizedString(forRegionCode: countryCode) ?? "")
                }
            }
        }
    }
}

struct ContentView_Previews: PreviewProvider {
    static var previews: some View {
        ContentView()
    }
}
