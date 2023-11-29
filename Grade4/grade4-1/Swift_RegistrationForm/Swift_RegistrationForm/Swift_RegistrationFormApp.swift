//
//  Swift_RegistrationFormApp.swift
//  Swift_RegistrationForm
//
//  Created by 張芯翎 on 2023/10/22.
//

import SwiftUI
import SwiftData

@main
struct Swift_RegistrationFormApp: App {
    var sharedModelContainer: ModelContainer = {
        let schema = Schema([
            Item.self,
        ])
        let modelConfiguration = ModelConfiguration(schema: schema, isStoredInMemoryOnly: false)

        do {
            return try ModelContainer(for: schema, configurations: [modelConfiguration])
        } catch {
            fatalError("Could not create ModelContainer: \(error)")
        }
    }()

    var body: some Scene {
        WindowGroup {
            ContentView()
        }
        .modelContainer(sharedModelContainer)
    }
}
