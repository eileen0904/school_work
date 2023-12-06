//
//  ContentView.swift
//  Swift_DataFiltering
//
//  Created by 張芯翎 on 2023/11/24.
//

import SwiftUI
import SwiftData

struct ContentView: View {
    var restaurants: [Restaurant] = [
        Restaurant(name: "For Kee Restaurant", type: "Hong Kong", location: "Shop J-K., 200 Hollywood Road, SOHO, Sheung Wan, Hong Kong",image: "forkeerestaurant"),
        Restaurant(name: "Traif", type: "American", location: "229 S 4th St Brooklyn, NY 11211", image: "traif"),
        Restaurant(name: "Donostia", type: "Spanish", location: "10 Seymour Place London W1H 7ND United Kingdom", image: "donostia"),
        Restaurant(name: "Royal Oak", type: "British", location: "2 Regency Street London SW1P 4BZ United Kingdom", image: "royaloak"),
        Restaurant(name: "CASK Pub and Kitchen", type: "Thai", location: "22 Charlwood Street London SW1V 2DY Pimlico", image: "caskpubkitchen")
    ]
    var types = ["All", "Hong Kong", "American", "Spanish", "British", "Thai"]
    @State var filterText = ""
    
    init() {
        let appear = UINavigationBarAppearance()
        let atters: [NSAttributedString.Key: Any] = [
            .font: UIFont(name: "AmericanTypewriter", size: 40)!
        ]

        appear.largeTitleTextAttributes = atters
        appear.titleTextAttributes = atters
        UINavigationBar.appearance().standardAppearance = appear
        UINavigationBar.appearance().compactAppearance = appear
        //UINavigationBar.appearance().scrollEdgeAppearance = appear
     }
    
    var filteredRestaurants: [Restaurant] {
        if filterText == "All" {
            return restaurants
        } else {
            return restaurants.filter { $0.type == filterText }
        }
    }
    
    var body: some View {
        NavigationView{
            ZStack{
                Color("Khaki1")
                    .ignoresSafeArea()
                VStack{
                    ScrollView(.horizontal, showsIndicators: true){
                        HStack{
                            ForEach(types, id: \.self){ option in
                                Button {
                                    filterText = option
                                } label:{
                                    Text(option)
                                        .padding(10)
                                        .background(filterText == option ? Color.blue : Color.gray)
                                        .foregroundColor(.white)
                                        .font(.custom("Times New Roman", size: 18))
                                        .cornerRadius(8)
                                }
                            }
                        } //HStack
                        .padding(.horizontal, 10)
                    } //scroll
                    
                    List{
                        ForEach(filteredRestaurants) { res in
                            NavigationLink {
                                RestaurantDetailView(restaurant: res)
                            } label: {
                                RestaurantList(restaurant: res)
                            }
                        }
                        .listRowBackground(Color.khaki1)
                        .listRowSeparatorTint(.black)
                    }
                    .listStyle(.plain)
                } //VStack
            }
            .navigationBarTitle (Text("Restaurants"))
        } //nav
    }
}

struct RestaurantList: View {
    var restaurant: Restaurant
    
    var body: some View {
        HStack {
            Image(restaurant.image)
                .resizable()
                .frame(width: 50, height: 50)
                .cornerRadius(8)
            Text(restaurant.name)
                .font(.custom("Times New Roman", size: 20))
                .fontWeight(.semibold)
        }
    }
}

struct RestaurantDetailView: View {
    var restaurant: Restaurant
    
    var body: some View {
        ZStack {
            Image(restaurant.image)
                .resizable()
                .scaledToFill()
                .frame(minWidth: 0,  maxWidth: .infinity, minHeight: 0,  maxHeight: .infinity)
                .clipped()
                .overlay(Color.black.opacity(0.3))
                .ignoresSafeArea()
            
            VStack {
                Text(restaurant.name)
                    .font(.custom("Georgia", size: 30))
                    .foregroundColor(.white)
                    .fontWeight(.bold)
                    .padding(4)
                Text("\(restaurant.type)")
                    .font(.custom("Georgia", size: 22))
                    .fontWeight(.medium)
                    .foregroundColor(.white)
                    .padding(4)
                Text("\(restaurant.location)")
                    .font(.custom("Georgia", size: 20))
                    .foregroundColor(.white)
            }
            .padding()
        }
        
        .navigationBarTitle(Text(""), displayMode: .inline)
    }
}

struct ContentView_Previews: PreviewProvider {
    static var previews: some View {
        ContentView()
    }
}
