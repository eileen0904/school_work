//
//  FinalProjectApp.swift
//  FinalProject
//
//  Created by 張芯翎 on 2023/11/29.
//

import SwiftUI
import SwiftData
import Firebase
import FirebaseAuth

@main
struct FinalProjectApp: App {
    @StateObject var data = AllDrinks()
    @StateObject var gd = GetData()
    
    init(){
        FirebaseApp.configure()
    }
    var body: some Scene {
        WindowGroup {
            if Auth.auth().currentUser != nil  {
                AppView()
                    .environmentObject(data)
                    .environmentObject(gd)
            } else {
                ContentView()
                    .environmentObject(data)
                    .environmentObject(gd)
            }
        }
    }
}
