//
//  AccountView.swift
//  FinalProject
//
//  Created by 張芯翎 on 2023/12/20.
//

import SwiftUI
import FirebaseAuth

struct AccountView: View{
    @State var showLogin = false
    
    var body: some View{
        ZStack{
            Color(Color.wootea)
                .ignoresSafeArea()
            
            VStack{
                VStack(alignment: .center){
                    Image("dog")
                        .resizable()
                        .scaledToFit()
                        .clipShape(Circle())
                        .frame(width: 150, height: 150)
                    if let user = Auth.auth().currentUser {
                        Text((user.displayName ?? "") as String)
                            .font(.custom("ZenOldMincho-Bold", size: 35))
                        Text((user.email ?? "") as String)
                            .font(.custom("ZenOldMincho-SemiBold", size: 20))
                    }
                }
                
                Rectangle()
                    .fill(.black)
                    .frame(width: 350, height: 1)
                
                VStack(alignment: .leading){
                    HStack{
                        Image("facebook")
                            .resizable()
                            .scaledToFit()
                            .frame(width: 45, height: 45)
                        Link("Wootea's Facebook", destination: URL(string: "https://www.facebook.com/WooTeaTW/")!)
                    }
                    HStack{
                        Image("instagram")
                            .resizable()
                            .scaledToFit()
                            .frame(width: 45, height: 45)
                        Link("Wootea's Instagram", destination: URL(string: "https://www.instagram.com/WooTeaTW/")!)
                    }
                    HStack{
                        Image("line")
                            .resizable()
                            .scaledToFit()
                            .frame(width: 45, height: 45)
                        Link("Wootea's Line", destination: URL(string: "https://line.me/R/ti/p/%40764rjimr")!)
                    }
                    HStack{
                        Image("youtube")
                            .resizable()
                            .scaledToFit()
                            .frame(width: 45, height: 45)
                        Link("Wootea's YouTube", destination: URL(string: "https://www.youtube.com/@wootea_official")!)
                    }
                    HStack{
                        Image("logo4")
                            .resizable()
                            .scaledToFit()
                            .frame(width: 45, height: 45)
                        Link("About Wootea", destination: URL(string: "https://www.wootea.com/")!)
                    }

                } // vstack
                .foregroundColor(.black)
                .font(.custom("ZenOldMincho-Regular", size: 23))
                
                Button{
                    do{
                        showLogin = true
                       try Auth.auth().signOut()
                    } catch {
                       print(error)
                    }
                } label: {
                    Text("Sign Out")
                        .foregroundColor(.white)
                        .font(.title2)
                        .fontWeight(.semibold)
                }
                .padding(15)
                .foregroundColor(.white)
                .background(Color.black)
                .cornerRadius(40)
                .fullScreenCover(isPresented: $showLogin){
                    ContentView()
                }
            } // vstack
        } // zstack
    } // body
}

struct AccountView_Previews: PreviewProvider {
    static var previews: some View {
        AccountView()
    }
}
