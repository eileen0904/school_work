//
//  HomeView.swift
//  FinalProject
//
//  Created by 張芯翎 on 2023/12/16.
//

import SwiftUI
import FirebaseFirestore
import FirebaseFirestoreSwift

struct HomeView: View{
    
    @FirestoreQuery(collectionPath: "drink") var drinks: [Drink]
    @FirestoreQuery var favorites: [Favorite]
    private let user_name: String

    var images = ["b1", "b2", "b3", "b4", "b5", "b6", "b7"]
    var types = ["所有飲品", "醇茶", "奶茶", "鮮奶", "奶霜", "農摘", "季節限定"]
    @State var filterText = ""
    
    init(user_name: String){
        self.user_name = user_name
        self._favorites = FirestoreQuery(collectionPath: "user/\(self.user_name)/favorite")
    }
    
    var filteredDrinks: [Drink]{
        if filterText == "所有飲品" {
            return drinks
        } else {
            return drinks.filter { $0.type == filterText }
        }
    }
        
    var body: some View{
        NavigationStack{
            ZStack{
                Color(Color.wootea)
                    .ignoresSafeArea()
                VStack{
                    Text("季節限定")
                        .foregroundColor(.black)
                        .font(.custom("ZenOldMincho-Bold", size: 40))
                        .padding(10)
                        .background(Color.newRed)
                        .cornerRadius(40)
                    
                    ScrollView(.horizontal){ // banner
                        HStack{
                            ForEach(images, id: \.self){ pic in
                                Image("\(pic)")
                                    .resizable()
                                    .frame(width:400, height:200)
                                    .shadow(radius:10, y:10)
                                    .scrollTransition(topLeading:.interactive, bottomTrailing: .interactive, axis:.horizontal){
                                        effect, phase in effect
                                            .scaleEffect(1 - abs(phase.value))
                                    }
                            }
                        }
                    } // scroll
                    
                    ScrollView(.horizontal){ // filter
                        HStack{
                            ForEach(types, id: \.self){ option in
                                Button{
                                    filterText = option
                                } label: {
                                    Text(option)
                                        .padding(10)
                                        .background(filterText == option ? Color.blue : Color.gray)
                                        .foregroundColor(.white)
                                        .font(.custom("ZenOldMincho-Regular", size: 18))
                                        .cornerRadius(8)
                                }
                            }
                        } // hstack
                        .padding(.horizontal, 10)
                    } // scroll

                    List{
                        ForEach(filteredDrinks){ tea in
                            NavigationLink{
                                if favorites.contains(where: { $0.name == tea.name }){
                                    TeaView(order: tea, user_name: user_name, isFill: true)
                                }
                                else{
                                    TeaView(order: tea, user_name: user_name, isFill: false)
                                }
                            } label: {
                                DrinkList(drink: tea)
                            }
                        }
                        .listRowBackground(Color.wootea)
                        .listRowSeparatorTint(.black)
                    }
                    .listStyle(.plain)
                } // vstack
                .scrollTargetBehavior(.viewAligned)
                .scrollTargetLayout()
                .scrollContentBackground(.hidden)
            } // zstack
        } // nav
    } // body
}

struct DrinkList: View{
    @State var drink: Drink
    
    var body: some View{
        HStack{
            Image(drink.name)
                .resizable()
                .scaledToFill()
                .frame(width: 50, height: 50)
                .clipped()
            
            Text(drink.name)
                .font(.custom("ZenOldMincho-Regular", size: 25))
                .multilineTextAlignment(.leading)
            
            Spacer()
            
            VStack{
                if(drink.Mprice == -1){
                    Text("L ：\(drink.Lprice)")
                }
                if(drink.Lprice == -1){
                    Text("M：\(drink.Mprice)")
                }
                if(drink.Lprice > 0 && drink.Mprice > 0){
                    Text("M：\(drink.Mprice)")
                    Text("L ：\(drink.Lprice)")
                }
            }
            .font(.custom("ZenOldMincho-Regular", size: 15))
        }
    } // body
}

struct HomeView_Previews: PreviewProvider {
    static var previews: some View {
        HomeView(user_name: "name")
            .environmentObject(AllDrinks())
            .environmentObject(GetData())
    }
}
