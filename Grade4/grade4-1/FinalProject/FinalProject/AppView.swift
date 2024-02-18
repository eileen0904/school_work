//
//  AppView.swift
//  FinalProject
//
//  Created by 張芯翎 on 2023/12/16.
//

import SwiftUI
import FirebaseFirestore
import FirebaseFirestoreSwift
import FirebaseAuth

struct AppView: View{
    
    @EnvironmentObject var data: AllDrinks
    @EnvironmentObject var gd: GetData
    
    init() {
        UITabBar.appearance().backgroundColor = UIColor.wootea
    }
    var body: some View{
        TabView{
            HomeView(user_name: gd.user_name)
                .tabItem{
                    Label("", systemImage: "house")
                }
            FavoriteView(user_name: gd.user_name)
                .tabItem{
                    Label("", systemImage: "heart")
                }
            OrderView(user_name: gd.user_name)
                .tabItem{
                    Label("", systemImage: "cart")
                }
            AccountView()
                .tabItem{
                    Label("", systemImage: "person")
                }
        }
        .tabViewStyle(DefaultTabViewStyle())
        .environmentObject(data)
        .environmentObject(gd)
    }
    
}

struct AppView_Previews: PreviewProvider {
    static var previews: some View {
        AppView()
            .environmentObject(AllDrinks())
            .environmentObject(GetData())
    }
}
