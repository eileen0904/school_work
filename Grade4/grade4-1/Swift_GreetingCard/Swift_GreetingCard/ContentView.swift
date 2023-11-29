//
//  ContentView.swift
//  Swift_GreetingCard
//
//  Created by 張芯翎 on 2023/10/11.
//

import SwiftUI
import SwiftData

struct ContentView: View {
    @State private var showAlert = false
    @State private var alertTitle = ""
    var body: some View {
        
        ZStack {
            LinearGradient(gradient: Gradient(colors: [Color("LightSkyBlue"), Color("LightSteelBlue")]), 
                           startPoint: UnitPoint(x: 0, y: 0), endPoint: UnitPoint(x: 1, y: 1))
                .ignoresSafeArea()
            VStack(spacing: 10){
                Text("Happy Birthday")
                    .fontWeight(.medium)
                    .font(.custom("DancingScript-Regular", size: 60))
                    .foregroundColor(.indigo)
                HStackText()
                Image("Uni")
                    .resizable()
                    .frame(width: 300, height: 300)
                    .cornerRadius(200)
                    .background(
                        Circle()
                        .padding(-15)
                        .foregroundColor(.orange)
                    )
                HStackUni()
                Button{
                    showAlert = true
                    alertTitle = "Uni's Birthday"
                } label: {
                    Image("cat_icon")
                        .frame(width: 20, height: 100)
                }
                .alert(alertTitle, isPresented: $showAlert, actions: {
                    Button("Meow") { }
                }, message: {
                    Text("Happy 1st birthday for my lovely cat Uni!!")
                })
            }
        }
    }
}

struct ContentView_Previews: PreviewProvider{
    static var previews: some View{
        ContentView()
    }
}

struct HStackText: View {
    var body: some View {
        HStack{
            Image("confetti")
                .resizable()
                .scaledToFit() //維持比例地佔滿可用空間
                .frame(width: 100, height: 100)
            Text("Uni")
                .fontWeight(.bold)
                .font(.custom("DancingScript-Regular", size: 100))
                .foregroundColor(.indigo)
            Image("balloon")
                .resizable()
                .scaledToFit()
                .frame(width: 100, height: 100)
        }
    }
}

struct HStackUni: View {
    var body: some View {
        HStack(spacing: 10) {
            Image("Uni1")
                .resizable()
                .scaledToFit()
                .frame(width: 100, height: 100)
                .background(
                    Rectangle()
                        .frame(width: 115, height: 110)
                        .foregroundColor(.darkGoldenrod)
                )
            Image("Uni2")
                .resizable()
                .scaledToFit()
                .frame(width: 100, height:100)
                .padding()
                .background(
                    Rectangle()
                        .frame(width: 115, height:80)
                        .foregroundColor(.white)
                )
            Image("Uni3")
                .resizable()
                .scaledToFit()
                .frame(width: 100, height:100)
                .background(
                    Rectangle()
                        .frame(width: 115, height:105)
                        .foregroundColor(.eyes)
                )
        }
    }
}
