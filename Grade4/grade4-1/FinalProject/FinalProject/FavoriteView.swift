//
//  FavoriteView.swift
//  FinalProject
//
//  Created by 張芯翎 on 2023/12/16.
//

import SwiftUI
import FirebaseFirestore
import FirebaseFirestoreSwift
import FirebaseAuth

struct FavoriteView: View {
    
    @FirestoreQuery var favorites: [Favorite]
    @FirestoreQuery(collectionPath: "drink") var drinks: [Drink]
    private let user_name: String
    @State var isFill = false
    
    init(user_name: String){
        self.user_name = user_name
        self._favorites = FirestoreQuery(collectionPath: "user/\(self.user_name)/favorite")
    }

    var body: some View{
        NavigationStack{
            ZStack{
                Color(Color.wootea)
                    .ignoresSafeArea()
                
                VStack {
                    Text("My Favorite")
                        .font(.custom("ZenMaruGothic-Bold", size: 40))
                        .foregroundColor(Color.newRed)
                        .padding()
                    List{
                        ForEach(favorites){ tea in
                            NavigationLink{
                                if let matchingDrink = drinks.first(where: { $0.name == tea.name }) {
                                    TeaView(order: matchingDrink, user_name: user_name, isFill: true)
                                }
                            } label: {
                                HStack(){
                                    Image("\(tea.name)")
                                        .resizable()
                                        .scaledToFill()
                                        .frame(width: 100, height: 150)
                                        .clipped()
                                    Text("\(tea.name)")
                                        .font(.custom("ZenMaruGothic-Medium", size: 25))
                                        .foregroundColor(.white)
                                        .multilineTextAlignment(.leading)
                                    
                                }
                                .padding()
                            }
                        } // for each
                        .listRowBackground(Color.newRed)
                        .listRowSeparatorTint(.white)
                    } // list
                    .listStyle(.plain)
                    .cornerRadius(15)
                    .scrollContentBackground(.hidden)
                    .padding()
                } // vstack
            } // zstack
        } // nav
    } // body
}

struct FavoriteView_Previews: PreviewProvider {
    static var previews: some View {
        FavoriteView(user_name: "name")
    }
}

