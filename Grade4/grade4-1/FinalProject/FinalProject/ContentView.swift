//
//  ContentView.swift
//  FinalProject
//
//  Created by 張芯翎 on 2023/11/29.
//

import SwiftUI
import SwiftData
import FirebaseAuth

struct ContentView: View {
    
    @State private var email = ""
    @State private var password = ""
    @State private var alertTitle = ""
    @State private var showAlert = false
    @State var showBool = false
    @EnvironmentObject var gd: GetData
    @EnvironmentObject var data: AllDrinks
    
    var body: some View {
        NavigationStack{
            ZStack{
                VStack{
                    Color(.white)
                        .ignoresSafeArea()
                    Color(.orange)
                        .ignoresSafeArea()
                }
                VStack{
                    Image("logo")
                        .resizable()
                        .scaledToFill()
                        .frame(width: 400, height: 400)
                    Spacer()
                    Group{
                        TextField("Email", text: $email, prompt: Text("Email"))
                            .textFieldStyle(.roundedBorder)
                            .padding()
                        SecureField("Password", text: $password)
                            .textFieldStyle(.roundedBorder)
                            .padding()
                    }
                    .font(Font.system(size: 25, design: .default))
                    Spacer()
                    
                    HStack(spacing: 30){
                        Button{
                            login()
                        } label: {
                            Text("Login")
                                .foregroundColor(.white)
                                .font(.title2)
                                .fontWeight(.semibold)
                        }
                        .padding()
                        .background(Color.black)
                        .cornerRadius(40)
                        .fullScreenCover(isPresented: $showBool){
                            AppView()
                        }
                        .alert(alertTitle, isPresented: $showAlert){
                            Button("OK"){}
                        } message: {
                            Text("")
                        }
                        NavigationLink {
                            SignUpView()
                        } label: {
                            Text("Sign Up")
                                .foregroundColor(.black)
                                .font(.title2)
                                .fontWeight(.semibold)
                        }
                        .padding()
                        .background(Color.white)
                        .cornerRadius(40)
                    }
                } // vstack
            } // zstack
        } // nav
        .environmentObject(gd)
        .environmentObject(data)
    } // body
    
    func login(){
        Auth.auth().signIn(withEmail: email, password: password){ result, error in
            guard error == nil else {
                if let message = error?.localizedDescription {
                    alertTitle = message
                }
                showAlert = true
                return
            }
            if let user = Auth.auth().currentUser{
                gd.user_name = user.displayName ?? ""
                gd.fav_path = "user/" + (user.displayName ?? "") + "/favorite"
                gd.order_path = "user/" + (user.displayName ?? "") + "/order"
                print("ContentView name:\(gd.user_name)")
                print("ContentView fav_path:\(gd.fav_path)")
                print("CintentView order_path:\(gd.order_path)")
            }
            alertTitle = "success"
            showBool = true
        }
    }
}

struct ContentView_Previews: PreviewProvider{
    static var previews: some View{
        ContentView()
            .environmentObject(GetData())
            .environmentObject(AllDrinks())
    }
}
