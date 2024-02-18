//
//  SignUpView.swift
//  FinalProject
//
//  Created by 張芯翎 on 2023/12/16.
//

import SwiftUI
import FirebaseAuth
import FirebaseFirestore
import FirebaseFirestoreSwift

struct SignUpView: View{
    
    @State private var email = ""
    @State private var name = ""
    @State private var password = ""
    @State private var copassword = ""
    @State private var alertTitle = ""
    
    // 控制圖片放大縮小
    @State private var isEditing = false
    @State private var showAlert = false
    
    @State private var offset: CGFloat = 20.0
    @State private var regisSuccess: Bool = false
    
    @EnvironmentObject var gd: GetData
    
    var body: some View{
        NavigationView{
            ZStack{
                Color(Color.wootea)
                    .ignoresSafeArea()
                VStack{
                    Image("logo2")
                        .resizable()
                        .scaledToFill()
                        .frame(width: isEditing ? 100 : 200, height: isEditing ? 100 : 200)
                        .animation(Animation.easeInOut(duration: 0.3), value: offset)
                    Form{
                        Section("Email"){
                            TextField("", text: $email, onEditingChanged: { editing in
                                self.isEditing = editing
                            })
                                .background(.white)
                                .foregroundColor(.black)
                        }
                        Section("Username"){
                            TextField("", text: $name, onEditingChanged: { editing in
                                self.isEditing = editing
                            })
                                .background(.white)
                                .foregroundColor(.black)
                        }
                        Section("Password"){
                            TextField("", text: $password, onEditingChanged: { editing in
                                self.isEditing = editing
                            })
                                .background(.white)
                                .foregroundColor(.black)
                        }
                        Section("Confirm Password"){
                            TextField("", text: $copassword, onEditingChanged: { editing in
                                self.isEditing = editing
                            })
                                .background(.white)
                                .foregroundColor(.black)
                        }
                    } // form
                    .foregroundColor(.black)
                    .font(.system(size: 15))
                    .fontWeight(.semibold)
                    .scrollContentBackground(.hidden)
                    
                    Button{
                        allAlert()
                    } label: {
                        Text("Register")
                            .foregroundColor(.white)
                            .font(.title2)
                            .fontWeight(.semibold)
                    }
                    .padding()
                    .foregroundColor(.white)
                    .background(Color.black)
                    .cornerRadius(40)
                    .alert(alertTitle, isPresented: $showAlert){
                        Button("OK"){}
                    } message: {
                        Text("")
                    }
                    
                    NavigationLink(destination: ContentView(), isActive: $regisSuccess) {}
                } // vstack
            } // zstack
        } // nav
    } // body
    
    func allAlert(){
        if email.isEmpty{
            alertTitle = "信箱 不能為空白"
            showAlert = true
        }
        else if name.isEmpty{
            alertTitle = "用戶名 不能為空白"
            showAlert = true
        }
        else if password.isEmpty{
            alertTitle = "密碼 不能為空白"
            showAlert = true
        }
        else if copassword.isEmpty{
            alertTitle = "確認密碼 不能為空白"
            showAlert = true
        }
        else if password != copassword{
            alertTitle = "密碼與確認密碼 不符合"
            showAlert = true
        }
        else{
            Auth.auth().createUser(withEmail: email, password: password) {result, error in
                guard let user = result?.user,
                    error == nil else {
                    if let message = error?.localizedDescription {
                        alertTitle = message
                        showAlert = true
                    }
                    return
                }
                if let currentUser = Auth.auth().currentUser?.createProfileChangeRequest(){
                    currentUser.displayName = name
                    currentUser.commitChanges(completion: {error in
                        if let message = error?.localizedDescription {
                            alertTitle = message
                            showAlert = true
                        } else {
                            gd.user_name = name
                            gd.fav_path = "user/" + name + "/favorite"
                            gd.order_path = "user/" + name + "/order"
                            alertTitle = "建立成功"
                            showAlert = true
                            regisSuccess = true
                        }
                    })
                }
            }
        }
    }
}

struct SignUpView_Previews: PreviewProvider {
    static var previews: some View {
        SignUpView()
    }
}
